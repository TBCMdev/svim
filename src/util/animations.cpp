#include "animations.hpp"
#include "../types.hpp"

namespace animations
{
    animation<screen_frame_t> old_monitor_boot(anim_time begin, color col, screen_frame_t& __screen, dimension_t xWidth, dimension_t yWidth)
    {
        animation<screen_frame_t> animation;

        // [TODO]: wont work if screen is resized.
        gapi::screen_char_data* flashLinePtr = &screen.at(xWidth * flashLineID);
        
        const auto _OMB_middle_flash = [&](anim_time curr, screen_frame_t& screen, std::shared_ptr<dynamic_keyframe<screen_frame_t>> kf) -> void
        {
            const static size_t            flashLineID  = (size_t) yWidth / 2;
            
            const auto speed = kf->speed;
            
            // ----
            auto sinceStart = curr - begin;
            size_t sinceFrames   = sinceStart / speed;

            if (sinceStart < (sinceFrames + 1) * speed) return;
            
        };
        
        const auto _OMB_expand = [&](anim_time curr, screen_frame_t& screen, std::shared_ptr<dynamic_keyframe<screen_frame_t>> kf) -> void
        {
            
        };

        std::shared_ptr<dynamic_keyframe<screen_frame_t>> flash = std::make_shared<dynamic_keyframe<screen_frame_t>>(begin, 1000, _OMB_middle_flash);
        animation.addKeyframe(flash);

        return animation;
    }

}