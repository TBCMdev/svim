#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

#include "../types.hpp"
#include "../util/color.hpp"

typedef int s_widget_anchor;
struct s_widget_content_inserter
{
    std::shared_ptr<std::string> cont;
    size_t at;
    bool constant;
};
struct s_widget
{
    position    pos;
    dimension_t width, height;
    
    s_widget_anchor anchor;
    color       backgroundColor = color{255, 0, 0}, foregroundColor = color{255, 255, 255};
    std::unique_ptr<std::vector<s_widget>> children = nullptr;
    
    char        filler     =  ' ';

    
    bool        anchored   = false;
    bool        scrollable = false;
    bool        editable   = false;

    std::unordered_map<size_t, std::vector<s_widget_content_inserter>> insersions;

    std::vector<std::string> lines;

    std::string drawContents();
    void setLine(size_t line, const std::string& str); 

    s_widget(position _pos, dimension_t _width, dimension_t _height, s_widget_anchor _anchor = 0x0)
        : pos(_pos), width(_width), height(_height), anchor(_anchor) {}
};
