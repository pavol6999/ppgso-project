#ifndef PPGSO_SPOTLIGHT_H
#define PPGSO_SPOTLIGHT_H


#include <array>
#include "src/scene.h"
#include "Light.h"
#include <glm/glm.hpp>

class Spotlight final : public Light {
public:
    glm::vec3 up{0,1,0};
    std::array<glm::vec3,4> colorLights;
    float constant = 1.f;
    float linear = 0.22f;
    float quadratic = 0.20f;
    glm::vec3 position;
    glm::vec3 center;

    glm::vec3 initial_center;
    float cutOff = glm::cos(glm::radians(25.f));
    float outerCutOff = glm::cos(glm::radians(30.0f));
    Spotlight(glm::vec3 position,glm::vec3 direction, int initial_color_index, float turn_on_time);
    bool update(Scene &scene, float dt) override;
};


#endif //PPGSO_SPOTLIGHT_H
