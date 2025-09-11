#include "animation.hpp"
template<typename _AnimT>
void animation<_AnimT>::animate(time_t current)
{
    if (nextKeyframeID == 0)
        startTime = current;
    if (!currentAnimatingKeyframe)
        currentAnimatingKeyframe = keyframes.at(nextKeyframeID++);

    if (nextKeyframeID >= keyframes.size())
    {
        if (finish)
            finish();
        return;
    }
    if (startTime + currentAnimatingKeyframe->when < current)
        return;
    
    if (std::shared_ptr<dynamic_keyframe<_AnimT>>
            functor = std::dynamic_pointer_cast<dynamic_keyframe<_AnimT>>(currentAnimatingKeyframe))
    {
        if (functor->_animate)
            functor->_animate(animatable);
    }
    else
    if (std::shared_ptr<static_keyframe<_AnimT>>
            statickf = std::dynamic_pointer_cast<static_keyframe<_AnimT>>(currentAnimatingKeyframe))
    {
        animatable = statickf->val;
    }
}