#ifndef PPGSO_ROULETTE_TABLE_H
#define PPGSO_ROULETTE_TABLE_H

#include "src/object.h"
#include "roulette_wheel.h"
#include <ppgso/ppgso.h>

class RouletteWheel;

class RouletteTable : public Object{
private:
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture;

    std::unique_ptr<RouletteWheel> wheel;

    friend class RouletteWheel;
public:

    RouletteTable(glm::vec3 pos, glm::vec3 rot);

    bool update(Scene &scene, float dt) override;

    void render(Scene &scene) override;
};
#endif //PPGSO_ROULETTE_TABLE_H
