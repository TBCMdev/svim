#include <iostream>


#include "src/graphics/widget.hpp"
#include "src/util/file.hpp"
#include "src/graphics/api/api.hpp"

int main(int argc, char** argv)
{
    if (argc < 2)
        return EXIT_FAILURE;

    const char* fileName = argv[1];

    auto fileContent = readfile(fileName);

    if(!fileContent)
        return EXIT_FAILURE;

    gapi::setup();

    std::pair<short, short> windowDimensions = gapi::getWindowDimensions();

    s_widget rootWidget({0, 0}, windowDimensions.first, windowDimensions.second);

    s_widget topWidget({0, 0}, windowDimensions.first, 1);

    topWidget.lines = {"23:51 - main.cpp (n lines) 00:00:00 session"};

    rootWidget.filler = '-';
    rootWidget.backgroundColor = {0, 0, 0};

    
    SET_CURSOR_VISIBILITY(false);

    gapi::util::writeCursorConfig();
    while(gapi::_g_RUNNING)
    {
#ifdef _WIN32
        // ShowScrollBar(gapi::_g_chwnd, SB_BOTH, FALSE);
        // SetConsoleScreenBufferSize(gapi::_g_stdhwnd, gapi::_g_cinfo.dwSize);

#endif
        // todo make into write func
        windowDimensions = gapi::getWindowDimensions();
        // dynamically resize root widget
        rootWidget.width  = windowDimensions.first;
        rootWidget.height = windowDimensions.second;

        gapi::refresh();
        // poll events

        // draw
        gapi::drawWidget(rootWidget);

        gapi::drawWidget(topWidget);
        // render
        gapi::render();

        // SET_CURSOR_VISIBILITY(true);

        Sleep(8);

    }
    gapi::util::restoreConsole();
    // ShowScrollBar(gapi::_g_chwnd, SB_RIGHT, TRUE);


    return EXIT_SUCCESS;
}