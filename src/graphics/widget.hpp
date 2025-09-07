#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <vector>


#include "../types.hpp"
#include "../util/color.hpp"

typedef int s_widget_anchor;

struct s_widget
{
    dimension_t width, height;
    position    pos;

    color       backgroundColor = color{255, 0, 0}, foregroundColor = color{255, 255, 255};
    
    std::unique_ptr<std::vector<s_widget>> children = nullptr;
    
    char        filler     =  ' ';

    s_widget_anchor anchor;
    
    bool        anchored   = false;
    bool        scrollable = false;
    bool        editable   = false;

    std::vector<std::string> lines;

    std::string drawContents() const;

    s_widget(position _pos, dimension_t _width, dimension_t _height, s_widget_anchor _anchor = 0x0)
        : pos(_pos), width(_width), height(_height), anchor(_anchor) {}
};
