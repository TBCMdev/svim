#include "widget.hpp"

#include <sstream>

std::string s_widget::drawContents() const
{
    std::stringstream stream;

    stream << backgroundColor.toansii() << foregroundColor.toansii();
    
    for(dimension_t i = 0; i < height; i++)
        for(dimension_t j = 0; j < width; j++)
            stream << filler;

    return stream.str() + ANSII_RESET;
}