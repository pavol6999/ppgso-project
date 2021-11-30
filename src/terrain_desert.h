//
// Created by FIIT STU on 11/29/2021.
//

#ifndef PPGSO_TERRAIN_DESERT_H
#define PPGSO_TERRAIN_DESERT_H

#include <ppgso.h>
#include "object.h"

class terrain_desert final : public Object {
private:
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture;

public:

    terrain_desert();

    bool update(Scene &scene, float dt) override;

    void render(Scene &scene) override;
};


#endif //PPGSO_TERRAIN_DESERT_H
