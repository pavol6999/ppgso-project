//
// Created by Administrator on 04/12/2021.
//

#ifndef PPGSO_ANIMATED_OBJECT_H
#define PPGSO_ANIMATED_OBJECT_H
#include "object.h"

class AnimatedObject : public Object {
public:
    struct key_frame {
        glm::vec3 duration;
        const glm::vec3 position = position;
        const glm::vec3 rotation = rotation;
        const glm::vec3 scale = scale;
        float age = 0;
    };

    void animate(float dt);

    std::vector<key_frame> key_frames;
private:
    size_t current_key = 0;

};

#endif //PPGSO_ANIMATED_OBJECT_H
