#include <iostream>
#include <ctime>
#include <format>

#include "src/session.hpp"
#include "src/graphics/widget.hpp"
#include "src/util/file.hpp"
#include "src/util/format.hpp"
#include "src/graphics/api/api.hpp"

int main(int argc, char** argv)
{
    if (argc < 2)
        return EXIT_FAILURE;

    std::string fileName = argv[1];

    auto fileContent = readfile(fileName.c_str());

    if(!fileContent)
        return EXIT_FAILURE;

    gapi::setup();

    std::pair<short, short> windowDimensions = gapi::getWindowDimensions();

    s_widget rootWidget({0, 0}, windowDimensions.first, windowDimensions.second);

    s_widget topWidget({0, 0}, windowDimensions.first, 1);


    rootWidget.filler = '-';
    rootWidget.backgroundColor = {0, 0, 0};

    
    SET_CURSOR_VISIBILITY(false);

    gapi::util::writeCursorConfig();

    session currentSession;

    while(gapi::_g_RUNNING)
    {
#ifdef _WIN32
        // ShowScrollBar(gapi::_g_chwnd, SB_BOTH, FALSE);
        // SetConsoleScreenBufferSize(gapi::_g_stdhwnd, gapi::_g_cinfo.dwSize);

#endif

        // poll events


        // todo make into write func
        windowDimensions = gapi::getWindowDimensions();
        // dynamically resize root widget
        rootWidget.width  = windowDimensions.first;
        rootWidget.height = windowDimensions.second;

        ctime(&currentSession.timestamp);
        currentSession.tm_timestamp = localtime(&currentSession.timestamp);

        /* WIDGET PREPPING */
        {
            std::string line = std::format("{}:{} - {} ({} lines) 00:00:00 session",
                                      currentSession.tm_timestamp->tm_hour,
                                      currentSession.tm_timestamp->tm_min,
                                      fileName,
                                      0);
            topWidget.setLine(0, line);
        }
        gapi::refresh();

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