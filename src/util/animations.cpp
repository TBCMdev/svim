#include "animations.hpp"

namespace animations
{
    animation<screen_frame_t> old_monitor_boot(color col)
    {
        animation<screen_frame_t> animation;

        keyframe<screen_frame_t> kf;
        kf.when = 0;
        kf.duration = 2;
        animation.keyframes.push_back(kf);

        return animation;
    }

}