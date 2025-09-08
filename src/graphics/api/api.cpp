#include "api.hpp"

namespace gapi
{

    std::pair<int, int> getWindowDimensions()
    {
#ifdef _WIN32
        return {S_CONSOLE_WIDTH, S_CONSOLE_HEIGHT};
#else
        return {0, 0};
#endif
    }

    DWORD setup()
    {
#ifdef _WIN32
        
        _g_chwnd   = GetConsoleWindow();
        _g_hdc     = GetDC(_g_chwnd);
        _g_stdhwnd = GetStdHandle(STD_OUTPUT_HANDLE);
        _g_cmode   = GetConsoleMode(_g_stdhwnd, &_g_cmode);

        // enable virtual processing (color support)

        DWORD copiedMode = _g_cmode;
        copiedMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

        // Try to set the mode.
        if (!SetConsoleMode(_g_stdhwnd, copiedMode))
            return ::GetLastError();

        DWORD error = refresh();
        if(error != EXIT_SUCCESS)
            return error;
        
        auto dimensions = getWindowDimensions();
        _g_cbuffer.reserve((size_t)(dimensions.first * dimensions.second));

#else
        
#endif
        return 0;
    }
    // refreshes globals
    DWORD refresh()
    {
#ifdef _WIN32
        // [TODO]: no error checks
        GetConsoleScreenBufferInfo(_g_stdhwnd, &_g_cinfo);
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

    void drawWidget(const s_widget& widget)
    {
#ifdef _WIN32
        RECT rect{widget.pos.x, widget.pos.y, widget.pos.x + widget.width, widget.pos.y + widget.height};
        const std::string widgetStr = widget.drawContents();
        // DrawTextA(_g_hdc, widgetStr.c_str(), (int)widgetStr.length(), &rect, widget.anchor);

        // fix...
        size_t _At = 0;
        for(size_t i = widget.pos.y; i < min(widget.pos.y + widget.height, S_CONSOLE_HEIGHT); i++)
        {
            for(size_t j = widget.pos.x; j < min(widget.pos.x + widget.width, S_CONSOLE_WIDTH); j++)
            {
                screen_char_data& info = _g_cbuffer.at((S_CONSOLE_WIDTH * i) + j);

                info.character.UnicodeChar = widgetStr.at(_At++);

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
        for (screen_char_data& charData : _g_cbuffer)
        {
            std::wstring output;
            if (charData.color_data)
            {
                auto& colorData = *charData.color_data;
                output = colorData.background.toansii() + colorData.foreground.toansii();
            }
            output.push_back(charData.character.UnicodeChar);
            output += ANSII_RESET_L;
            DWORD success;
            WriteConsoleA(_g_stdhwnd, output.c_str(), (DWORD)output.length(), &success, NULL);
            if (!success) {}
                // error
        }
    }
};

