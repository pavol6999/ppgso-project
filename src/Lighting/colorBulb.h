#ifndef PPGSO_COLORBULB_H
#define PPGSO_COLORBULB_H


#include <array>
#include "src/Lighting/Light.h"
#include "src/scene.h"
class ColorBulb final : public Light{

public:
    bool animate = true;
    float constant = 1.0f;
    float linear = 0.09f;
    float quadratic = 0.032f;
    std::array<glm::vec3,4> colorLights;
    ColorBulb(glm::vec3 position, int initial_color_index, float turn_on_time);
    bool update(Scene &scene, float dt) override;
};

#endif //PPGSO_COLORBULB_H
