#pragma once

#include <cstdint>
#include <string>

#define ANSII_FOREGROUND "38;2;"
#define ANSII_BACKGROUND "48;2;"
#define ANSII_ESC "\x1b["

#define ANSII_RESET ANSII_ESC "0m"
struct color
{
    uint8_t r, g, b;

    std::string toansii(bool background = false) const;

};