//
// Created by FIIT STU on 12/11/2021.
//

#ifndef PPGSO_COLORBULB_H
#define PPGSO_COLORBULB_H

#include "src/scene.h"
#include "src/Lighting/Light.h"

class ColorBulb : public Light{

public:
    float constant = 1.0f;
    float linear = 0.09f;
    float quadratic = 0.032f;
    std::array<glm::vec3,4> colorLights;
    ColorBulb(glm::vec3 position, int initial_color_index);
    bool update(Scene &scene, float dt) override;
};

#endif //PPGSO_COLORBULB_H
