//
// Created by Administrator on 30/11/2021.
//

#ifndef PPGSO_DOORS_H
#define PPGSO_DOORS_H

#include <ppgso.h>
#include "object.h"

class Doors final : public Object {
private:
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture;

public:
    Doors(glm::vec3 pos);

    void animate(float dt);

    bool update(Scene &scene, float dt) override;

    void render(Scene &scene) override;
};

#endif //PPGSO_DOORS_H
