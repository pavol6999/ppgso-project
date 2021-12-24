#ifndef PPGSO_ROULETTE_WHEEL_H
#define PPGSO_ROULETTE_WHEEL_H

#include "src/object.h"
#include "roulette_moving.h"
#include "roulette_table.h"

#include <ppgso/ppgso.h>

class RouletteTable;
class RouletteMoving;

class RouletteWheel : public Object{
private:
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture;

    RouletteTable &table;

    std::unique_ptr<RouletteMoving> moving;

    friend class RouletteMoving;
public:

    RouletteWheel(RouletteTable &parent);

    bool update(Scene &scene, float dt) override;

    void render(Scene &scene) override;
};
#endif //PPGSO_ROULETTE_WHEEL_H
