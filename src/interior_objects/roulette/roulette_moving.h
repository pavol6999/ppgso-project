//
// Created by Administrator on 07/12/2021.
//

#ifndef PPGSO_ROULETTE_MOVING_H
#define PPGSO_ROULETTE_MOVING_H
#include "src/object.h"
#include <ppgso/ppgso.h>

class RouletteMoving : public Object{
private:
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture;

public:

    RouletteMoving(glm::vec3 pos, glm::vec3 rot, glm::vec3 sc);

    bool update(Scene &scene, float dt) override;

    void render(Scene &scene) override;
};
#endif //PPGSO_ROULETTE_MOVING_H
