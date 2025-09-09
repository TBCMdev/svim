#include <iostream>
#include <ctime>
#include <chrono>
#include <format>

#include "src/util/animation.hpp"
#include "src/util/animations.hpp"

#include "src/session.hpp"
#include "src/graphics/widget.hpp"
#include "src/util/file.hpp"
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


    rootWidget.backgroundColor = {0, 0, 0};

    
    SET_CURSOR_VISIBILITY(false);

    gapi::util::writeCursorConfig();

    session currentSession;
    currentSession.sessionBegin = std::chrono::steady_clock::now();

    std::string& realFileContent = *fileContent;
    size_t lineCount             = std::count(realFileContent.begin(), realFileContent.end(), '\n');
    currentSession.currentFileInfo = std::make_unique<file_info>(lineCount, realFileContent);

    time(&currentSession.timestamp);


    auto _run = [&]() -> void
    {
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

            time(&currentSession.timestamp);
            currentSession.tm_timestamp = localtime(&currentSession.timestamp);
            auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - currentSession.sessionBegin).count();

            currentSession.sessionHours = elapsed / 3600;
            currentSession.sessionMinutes = (elapsed % 3600) / 60;
            currentSession.sessionSeconds = elapsed % 60;

            /* WIDGET PREPPING */
            {
                std::string line = std::format("{:02}:{:02} - {} ({} lines) {:02}:{:02}:{:02} (stime)",
                                        currentSession.tm_timestamp->tm_hour,
                                        currentSession.tm_timestamp->tm_min,
                                        fileName,
                                        currentSession.currentFileInfo ? currentSession.currentFileInfo->lineCount : '?',
                                        currentSession.sessionHours,
                                        currentSession.sessionMinutes,
                                        currentSession.sessionSeconds);
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
    };
    
    animation bootAnim = animations::old_monitor_boot({220, 220, 220});
    bootAnim.finish = _run;
    bootAnim.animate(currentSession.timestamp);
    
    return EXIT_SUCCESS;
}