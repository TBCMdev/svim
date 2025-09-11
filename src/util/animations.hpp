#pragma once

#include <string>

#include "../api/screen_data.hpp"
#include "../util/color.hpp"

#include "animation.hpp"
namespace animations
{
    typedef std::vector<gapi::screen_char_data> screen_frame_t;
    animation<screen_frame_t> old_monitor_boot(time_t begin, color col, screen_frame_t& __screen, dimension_t xWidth, dimension_t yWidth);
}