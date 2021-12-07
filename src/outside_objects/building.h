//
// Created by Administrator on 27/11/2021.
//

#ifndef PPGSO_BUILDING_H
#define PPGSO_BUILDING_H

#include <src/object.h>
#include <mesh.h>

class Building final : public Object {
private:
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture;

public:

    Building();

    bool update(Scene &scene, float dt) override;

    void render(Scene &scene) override;
};


#endif //PPGSO_BUILDING_H
