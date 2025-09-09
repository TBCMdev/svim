#include "animation.hpp"
template<typename _AnimT>
void animation<_AnimT>::animate(time_t current)
{
    if (currentAnimatingKeyframe == 0)
        startTime = current;

    if (currentAnimatingKeyframe >= keyframes.size())
    {
        if (finish)
            finish();
        return;
    }
    keyframe<_AnimT>& currentKeyframe = keyframes.at(currentAnimatingKeyframe);

    if (currentKeyframe.when < current)
        return;
    
    currentKeyframe.began = current;

    if (currentKeyframe.animate)
        currentKeyframe.animate(animatable);
    else
        animatable = currentKeyframe.val;
}