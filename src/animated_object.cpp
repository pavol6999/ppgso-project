#include "animated_object.h"

void AnimatedObject::animate(float dt) {
    if (current_key == key_frames.size() - 1) {
        return;
    }

    position += (dt*(key_frames[current_key + 1].position - key_frames[current_key].position))/key_frames[current_key].duration;
    rotation += (dt*(key_frames[current_key + 1].rotation - key_frames[current_key].rotation))/key_frames[current_key].duration;
    scale += (dt*(key_frames[current_key + 1].rotation - key_frames[current_key].rotation))/key_frames[current_key].duration;

    key_frames[current_key].age += dt;

    if (key_frames[current_key].age >= key_frames[current_key].duration.x) {
        current_key++;
    }
}

