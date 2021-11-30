//
// Created by Administrator on 23/11/2021.
//

#ifndef PPGSO_SKYBOX_H
#define PPGSO_SKYBOX_H

#include <ppgso.h>
#include "object.h"

class SkyBox final : public Object {
private:
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture;

public:
    SkyBox() = default;
    SkyBox(glm::vec3 scale);


    bool update(Scene &scene, float dt) override;

    void render(Scene &scene) override;
};

#endif //PPGSO_SKYBOX_H
