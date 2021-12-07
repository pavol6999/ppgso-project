//
// Created by Administrator on 06/12/2021.
//

#ifndef PPGSO_SCREEN_H
#define PPGSO_SCREEN_H

#include "src/object.h"
#include <ppgso/ppgso.h>

class Screen : public Object{
private:
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture;

    glm::vec2 textureOffset;
public:

    Screen(glm::vec3 pos, glm::vec3 rot, glm::vec3 sc);

    bool update(Scene &scene, float dt) override;

    void render(Scene &scene) override;
};

#endif //PPGSO_SCREEN_H
