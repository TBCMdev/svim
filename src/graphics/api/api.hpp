#pragma once
#include <utility>
#include <memory>

#define UNIVERSAL

#ifdef _WIN32
#include <windows.h>
#endif

#include "../widget.hpp"

namespace gapi
{
    UNIVERSAL struct screen_color_data
    {
        color foreground, background;

        screen_color_data(const color& _fg, const color& _bg) : foreground(_fg), background(_bg) {}
    };
    UNIVERSAL struct screen_char_data
    {
        std::unique_ptr<screen_color_data> color_data;
        union {
            WCHAR UnicodeChar;
            CHAR   AsciiChar;
        } character;
    };
    UNIVERSAL
    inline std::vector<screen_char_data> _g_cbuffer;
#ifdef _WIN32
    // windows globals
    inline HANDLE                        _g_stdhwnd;
    inline HWND                          _g_chwnd;
    inline DWORD                         _g_cmode;
    inline HDC                           _g_hdc;
    inline CONSOLE_SCREEN_BUFFER_INFO    _g_cinfo;

    
#define S_CONSOLE_WIDTH _g_cinfo.srWindow.Left - 1
#define S_CONSOLE_HEIGHT _g_cinfo.srWindow.Top + 1
#endif

    DWORD                         clear();
    DWORD                         refresh();

    DWORD                         setup();
    std::pair<int, int>           getWindowDimensions();

    void                          drawWidget(const s_widget& widget);
    void                          render();
}