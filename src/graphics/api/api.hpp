#pragma once
#include <utility>
#include <memory>

#define UNIVERSAL

#ifdef _WIN32
#include <windows.h>
#endif

#include "../widget.hpp"

#define CURSOR_HOME_ESC "\x1b[H"
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
    inline bool                          _g_RUNNING = true;
    inline std::vector<screen_char_data> _g_cbuffer;


#ifdef _WIN32
    // windows globals
    inline HANDLE                        _g_stdhwnd;
    inline HANDLE                        _g_stdhwndi;
    inline HWND                          _g_chwnd;
    inline DWORD                         _g_cmode;
    inline DWORD                         _g_cmodei;
    inline HDC                           _g_hdc;
    inline CONSOLE_SCREEN_BUFFER_INFO    _g_cinfo;
    inline CONSOLE_CURSOR_INFO           _g_cursor;

    inline DWORD                         _g_origcmode;
    inline DWORD                         _g_origcmodei;
    inline CONSOLE_CURSOR_INFO           _g_origcursor;
    
#define S_CONSOLE_WIDTH ((_g_cinfo.srWindow.Right - _g_cinfo.srWindow.Left) + (short)1)
#define S_CONSOLE_HEIGHT ((_g_cinfo.srWindow.Bottom - _g_cinfo.srWindow.Top) + (short)1)


#define SET_CURSOR_VISIBILITY(b) gapi::_g_cursor.bVisible = b;

#endif

    DWORD                         clear();
    DWORD                         refresh();

    DWORD                         setup();
    std::pair<short, short>           getWindowDimensions();

    void                          drawWidget(const s_widget& widget);
    void                          render();

    namespace internal
    {
        BOOL WINAPI _i_consoleHandler(DWORD signal);
    }

    namespace util
    {
        void writeCursorConfig();
        void restoreConsole();
    }
}