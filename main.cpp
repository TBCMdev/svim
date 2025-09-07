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

    std::pair<int, int> windowDimensions = gapi::getWindowDimensions();

    s_widget fileEditor({0, 0}, windowDimensions.first, windowDimensions.second);

    fileEditor.filler = '-';

    while(1)
    {
        gapi::clear();

        // poll events

        // clear

        // draw

        gapi::drawWidget(fileEditor);

    }

    return EXIT_SUCCESS;
}