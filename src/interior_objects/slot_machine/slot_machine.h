//
// Created by Administrator on 06/12/2021.
//

#ifndef PPGSO_SLOT_MACHINE_H
#define PPGSO_SLOT_MACHINE_H

#include "src/object.h"
#include <ppgso/ppgso.h>
#include "screen.h"

class SlotMachine : public Object{
private:
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture;

    std::unique_ptr<Screen> screen;

public:

    SlotMachine(glm::vec3 pos, glm::vec3 rot);

    bool update(Scene &scene, float dt) override;

    void render(Scene &scene) override;
};

#endif //PPGSO_SLOT_MACHINE_H
