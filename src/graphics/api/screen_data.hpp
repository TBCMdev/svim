#pragma once
#include <memory>
#include "../../util/color.hpp"
namespace gapi
{
    struct screen_color_data
    {
        color foreground, background;

        screen_color_data(const color& _fg, const color& _bg) : foreground(_fg), background(_bg) {}
    };
    struct screen_char_data
    {
        std::unique_ptr<screen_color_data> color_data;
        union {
            wchar_t UnicodeChar;
            char   AsciiChar;
        } character;
    };
}