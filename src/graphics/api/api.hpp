#pragma once
#include <utility>

#ifdef _WIN32
#include <windows.h>
#endif

#include "../widget.hpp"

namespace gapi
{


#ifdef _WIN32
    // windows globals
    inline HANDLE                     _g_stdhwnd;
    inline HWND                       _g_chwnd;
    inline DWORD                      _g_cmode;
    inline HDC                        _g_hdc;
    inline CONSOLE_SCREEN_BUFFER_INFO _g_cinfo;

    inline std::vector<CHAR_INFO>    _g_cbuffer;
#define S_CONSOLE_WIDTH _g_cinfo.srWindow.Left - 1
#define S_CONSOLE_HEIGHT _g_cinfo.srWindow.Top + 1
#endif

    DWORD                         clear();
    DWORD                         refresh();

    DWORD                         setup();
    std::pair<int, int>           getWindowDimensions();

    void                          drawWidget(const s_widget& widget);
}