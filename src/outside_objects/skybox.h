#ifndef PPGSO_SKYBOX_H
#define PPGSO_SKYBOX_H

#include <ppgso.h>
#include "src/animated_object.h"

class SkyBox final : public AnimatedObject {
private:
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture;

public:
    SkyBox();
    SkyBox(glm::vec3 scale);


    bool update(Scene &scene, float dt) override;

    void render(Scene &scene) override;
};

#endif //PPGSO_SKYBOX_H
