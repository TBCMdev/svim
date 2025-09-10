#include "animation.hpp"
template<typename _AnimT>
void animation<_AnimT>::animate(time_t current)
{
    if (currentAnimatingKeyframeID == 0)
        startTime = current;

    if (currentAnimatingKeyframeID >= keyframes.size())
    {
        if (finish)
            finish();
        return;
    }
    std::shared_ptr<keyframe<_AnimT>> currentKeyframe = keyframes.at(currentAnimatingKeyframeID);

    if (currentKeyframe->when < current)
        return;
    
    currentKeyframe->began = current;

    if (std::shared_ptr<dynamic_keyframe<_AnimT>>
            functor = std::dynamic_pointer_cast<dynamic_keyframe<_AnimT>>(currentKeyframe))
    {
        if (functor->_animate)
            functor->_animate(animatable);
    }
    else
    if (std::shared_ptr<static_keyframe<_AnimT>>
            statickf = std::dynamic_pointer_cast<static_keyframe<_AnimT>>(currentKeyframe))
    {
        animatable = statickf->val;
    }
}