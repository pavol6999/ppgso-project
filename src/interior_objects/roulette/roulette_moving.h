//
// Created by Administrator on 07/12/2021.
//

#ifndef PPGSO_ROULETTE_MOVING_H
#define PPGSO_ROULETTE_MOVING_H
#include "src/object.h"
#include <ppgso/ppgso.h>
#include "roulette_wheel.h"

class RouletteWheel;

class RouletteMoving : public Object{
private:
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture;

    RouletteWheel &wheel;
public:

    RouletteMoving(RouletteWheel &parent);

    bool update(Scene &scene, float dt) override;

    void render(Scene &scene) override;
};
#endif //PPGSO_ROULETTE_MOVING_H
