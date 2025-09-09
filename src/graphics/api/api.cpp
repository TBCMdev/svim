#include "api.hpp"

namespace gapi
{
    namespace internal
    {
        BOOL WINAPI _i_consoleHandler(DWORD signal)
        {
            switch(signal)
            {
                case CTRL_C_EVENT:
                case CTRL_BREAK_EVENT:
                    _g_RUNNING = false;
                    return TRUE;
                default:
                    return FALSE;
            }
        }        
    }
    namespace util
    {
        
        void writeCursorConfig()
        {
            SetConsoleCursorInfo(_g_stdhwnd, &_g_cursor);
        }
        void restoreConsole()
        {
            // Restore console mode
            SetConsoleMode(_g_stdhwnd, _g_origcmode);
            SetConsoleMode(_g_stdhwndi, _g_origcmodei);
            // Restore cursor visibility
            SetConsoleCursorInfo(_g_stdhwnd, &_g_origcursor);

            // Reset colors and move cursor home
            std::cout << "\x1b[0m" << "\x1b[H";  // move cursor to top-left
        }

    }
    std::pair<short, short> getWindowDimensions()
    {
#ifdef _WIN32
        return {(short)S_CONSOLE_WIDTH, (short)S_CONSOLE_HEIGHT};
#else
        return {0, 0};
#endif
    }

    DWORD setup()
    {
#ifdef _WIN32
        
        _g_chwnd    = GetConsoleWindow();
        _g_hdc      = GetDC(_g_chwnd);
        _g_stdhwnd  = GetStdHandle(STD_OUTPUT_HANDLE);
        _g_stdhwndi = GetStdHandle(STD_INPUT_HANDLE);
        _g_cmode    = GetConsoleMode(_g_stdhwnd, &_g_cmode);
        _g_cmodei   = GetConsoleMode(_g_stdhwndi, &_g_cmodei);
        
        

        GetConsoleCursorInfo(_g_stdhwnd, &_g_cursor);
        // enable virtual processing (color support)

        _g_origcmode  = _g_cmode;
        _g_origcmodei = _g_cmodei;
        _g_origcursor = _g_cursor;
        DWORD copiedMode = _g_cmode;

        copiedMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

        if (!SetConsoleMode(_g_stdhwnd, copiedMode))
            return ::GetLastError();

        DWORD copiedModeI = _g_cmodei | ENABLE_EXTENDED_FLAGS;
        copiedModeI      &= ~ENABLE_QUICK_EDIT_MODE;
        
        if (!SetConsoleMode(_g_stdhwndi, copiedModeI))
            return ::GetLastError();

        DWORD error = refresh();
        if(error != EXIT_SUCCESS)
            return error;
        
        auto dimensions = getWindowDimensions();
        _g_cbuffer.resize((size_t)(dimensions.first * dimensions.second));


        if (!SetConsoleCtrlHandler(internal::_i_consoleHandler, TRUE))
        {
            std::cerr << "Error: could not set control handler.\n";
            return EXIT_FAILURE;
        }



#else
        
#endif
        return 0;
    }
    // refreshes globals
    DWORD refresh()
    {
#ifdef _WIN32
        GetConsoleScreenBufferInfo(_g_stdhwnd, &_g_cinfo);

        auto size   = getWindowDimensions();
        _g_cbuffer.resize(size.first * size.second);

        COORD newBuffer = {
            (SHORT) max(_g_cinfo.dwSize.X, size.first),
            (SHORT) max(_g_cinfo.dwSize.Y, size.second)
        };
        SetConsoleScreenBufferSize(_g_stdhwnd, newBuffer);


        SMALL_RECT windowRect = { 0, 0, size.first - 1, size.second - 1 };
        SetConsoleWindowInfo(_g_stdhwnd, TRUE, &windowRect);
        // [TODO]: no error checks

        SetConsoleCursorPosition(_g_stdhwnd, {0, 0});

#else
        
#endif

        return 0;
    }

    DWORD clear()
    {
#ifdef _WIN32
    DWORD written = 0;
    PCWSTR sequence = L"\x1b[2J";
    if (!WriteConsoleW(_g_stdhwnd, sequence, (DWORD)wcslen(sequence), &written, NULL))
    {
        // If we fail, try to restore the mode on the way out.
        SetConsoleMode(_g_stdhwnd, _g_cmode);
        return ::GetLastError();
    }
#else

#endif
        return 0;
    }

    void drawWidget(s_widget& widget)
    {
#ifdef _WIN32
        RECT rect{widget.pos.x, widget.pos.y, widget.pos.x + widget.width, widget.pos.y + widget.height};
        const std::string widgetStr = widget.drawContents();
        const size_t widgetContentLength = widgetStr.length();
        // DrawTextA(_g_hdc, widgetStr.c_str(), (int)widgetStr.length(), &rect, widget.anchor);

        // fix...
        size_t _At = 0;
        for(size_t i = widget.pos.y; i < min(widget.pos.y + widget.height, S_CONSOLE_HEIGHT); i++)
        {
            for(size_t j = widget.pos.x; j < min(widget.pos.x + widget.width, S_CONSOLE_WIDTH); j++)
            {
                screen_char_data& info = _g_cbuffer.at((S_CONSOLE_WIDTH * i) + j);
                #ifdef UNICODE_CHAR_DISPLAY
                    info.character.UnicodeChar = _At < widgetContentLength ? widgetStr.at(_At++) : widget.filler;
                #else
                    info.character.AsciiChar   = _At < widgetContentLength ? widgetStr.at(_At++) : widget.filler;
                #endif
                info.color_data = std::make_unique<screen_color_data>(widget.foregroundColor, widget.backgroundColor);
            }
        }
        /*
        012345678901
        -*****------
        234567890123
        -*   *------
        -*   *------
        -*****------

        pos = (1, 0);
        width = 5;
        height = 4;
        1,2,3,4,5 -> 13,14,15,16,17 -> 

         */
        // WriteConsoleOutputCharacterA(_g_stdhwnd, widgetStr.c_str(), widgetStr.length(), COORD)

#else
        
#endif
    }
    void render()
    {
        std::string buffer;
        buffer.reserve(_g_cbuffer.size() * 16); // preallocate to reduce reallocations

        for (screen_char_data& charData : _g_cbuffer)
        {
            if (charData.color_data)
            {
                auto& colorData = *charData.color_data;
                buffer += colorData.background.toansii(true);
                buffer += colorData.foreground.toansii(false);
            }
            buffer.push_back(charData.character.AsciiChar);
            buffer += ANSII_RESET; // reset
        }

        DWORD written;
        WriteConsoleA(_g_stdhwnd, buffer.c_str(), static_cast<DWORD>(buffer.size()), &written, NULL);
    }
};

