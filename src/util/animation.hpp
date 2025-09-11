#pragma once
#include <vector>
#include <functional>
#include <chrono>

typedef std::chrono::time_point<std::chrono::steady_clock> anim_time;


template<typename _AnimT>
struct keyframe
{
    size_t when = 0, duration;
    std::chrono::milliseconds speed = 250; // how many updates per second
};
// no animation, just holds the val object.
template<typename _AnimT> 
struct static_keyframe : public keyframe<_AnimT>
{
    _AnimT val;
};
// can animate using l-interp for example using a function
template<typename _AnimT> 
struct dynamic_keyframe : public keyframe<_AnimT>
{
    size_t update_count = 0;
    bool (*_animate)(anim_time curr, _AnimT&, std::shared_ptr<dynamic_keyframe<screen_frame_t>>) = nullptr;

    dynamic_keyframe(anim_time curr, size_t when, size_t duration, void (*__animFunc)(_AnimT&, std::shared_ptr<dynamic_keyframe<screen_frame_t>>)) :
                        keyframe<_AnimT>{when, duration}, _animate(__animFunc)
    { }


    inline void animate()
    {
        update_count++;
        if (_animate)
        {
            if (_animate())
                update_count = 0;
        }
    }
};

template<typename _AnimT>
class animation
{
public:
    std::vector<std::shared_ptr<keyframe<_AnimT>>> keyframes;

    _AnimT animatable;

    anim_time startTime = 0;

    size_t                            nextKeyframeID = 0;
    std::shared_ptr<keyframe<_AnimT>> currentAnimatingKeyframe   = nullptr;

    std::function<void()> finish = nullptr;
    animation(const _AnimT& v, bool start = false) : animatable(v)
    {
        if (start)
            animate();
    }
    animation()
    { }

    inline bool finished()
    {
        return currentAnimatingKeyframe == nullptr;
    }

    inline bool tryAnimate(time_t curr)
    {
        if (startTime != 0 && startTime >= curr)
            animate(curr);
    }
    void animate(time_t curr);

    inline void addKeyframe(std::shared_ptr<static_keyframe<_AnimT>> kf)
    {
        keyframes.push_back(kf);
    }
    inline void addKeyframe(std::shared_ptr<dynamic_keyframe<_AnimT>> kf)
    {
        keyframes.push_back(kf);
    }
};