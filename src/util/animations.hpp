#pragma once

#include <string>

#include "../api/screen_data.hpp"
#include "../util/color.hpp"

#include "animation.hpp"
namespace animations
{
    typedef std::vector<gapi::screen_char_data> screen_frame_t;

    animation<screen_frame_t> old_monitor_boot(color col);
}