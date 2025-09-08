#include "color.hpp"

std::string color::toansii(bool background) const
{
    std::string rgb = std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b);
    return std::string(ANSII_ESC) + (background ? ANSII_BACKGROUND : ANSII_FOREGROUND) + rgb + "m";
}