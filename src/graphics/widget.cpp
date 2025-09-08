#include "widget.hpp"

#include <sstream>

std::string s_widget::drawContents() const
{
    std::stringstream stream;

    for(size_t i = 0; i < lines.size(); i++)
        stream << lines.at(i);
    return stream.str();
}