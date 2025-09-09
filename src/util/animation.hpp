#pragma once
#include <vector>
#include <functional>
template<typename _AnimT>
struct keyframe
{
    size_t when = 0, duration;
    
    time_t began = 0;

    _AnimT val;

    void (*animate)(_AnimT&) = nullptr;
};

template<typename _AnimT>
class animation
{
public:
    std::vector<keyframe> keyframes;

    _AnimT animatable;

    time_t startTime = 0;

    size_t currentAnimatingKeyframe = 0;

    std::function<void()> finish = nullptr;

    animation(const _AnimT& v, bool start = false) : animatable(v)
    {
        if (start)
            animate();
    }
    animation()
    { }

    inline bool tryAnimate(time_t curr)
    {
        if (startTime != 0 && startTime >= curr)
            animate(curr);
    }

    void animate(time_t curr);

};