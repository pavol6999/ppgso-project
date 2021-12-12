//
// Created by Administrator on 10/12/2021.
//

#ifndef PPGSO_ARM_H
#define PPGSO_ARM_H


#include "src/object.h"
#include <ppgso/ppgso.h>
#include "human.h"

class Human;

class Arm : public Object{
private:
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture;

    Human &human;
public:

    Arm(Human &parent);

    bool update(Scene &scene, float dt) override;

    void render(Scene &scene) override;
};


#endif //PPGSO_ARM_H
