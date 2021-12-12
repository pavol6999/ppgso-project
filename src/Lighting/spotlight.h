//
// Created by FIIT STU on 12/12/2021.
//

#ifndef PPGSO_SPOTLIGHT_H
#define PPGSO_SPOTLIGHT_H


#include <array>

#include "Light.h"
#include <glm/glm.hpp>

class Spotlight final : public Light {
public:

    std::array<glm::vec3,4> colorLights;
    float cutOff = glm::cos(glm::radians(12.5f));
    float outerCutOff = glm::cos(glm::radians(15.0f));
    Spotlight(glm::vec3 position,glm::vec3 direction, int initial_color_index);
    bool update(Scene &scene, float dt) override;
};


#endif //PPGSO_SPOTLIGHT_H
