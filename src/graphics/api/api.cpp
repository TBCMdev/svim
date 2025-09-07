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
        for(size_t i = widget.pos.y; i < min(widget.pos.y + widget.height, S_CONSOLE_HEIGHT); i++)
        {
            for(size_t j = widget.pos.x; j < min(widget.pos.x + widget.width, S_CONSOLE_WIDTH); j++)
            {
                CHAR_INFO& info = _g_cbuffer.at(j + (widget.width * i));
            }
        }
        // WriteConsoleOutputCharacterA(_g_stdhwnd, widgetStr.c_str(), widgetStr.length(), COORD)

#else
        
#endif
    }
};

