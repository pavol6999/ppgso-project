//
// Created by FIIT STU on 12/11/2021.
//

#ifndef PPGSO_SUN_H
#define PPGSO_SUN_H

#include "src/scene.h"
#include "src/Lighting/Light.h"

class Sun final : public Light{

public:
    std::array<glm::vec3,4> colorLights;
    Sun(int id, glm::vec3 position);
    bool update(Scene &scene, float dt) override;
};


#endif //PPGSO_SUN_H
