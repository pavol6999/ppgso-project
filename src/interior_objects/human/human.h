#ifndef PPGSO_HUMAN_H
#define PPGSO_HUMAN_H

#include "src/object.h"
#include "arm.h"
#include <ppgso/ppgso.h>

class Arm;

class Human : public Object{
private:
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture;

    std::unique_ptr<Arm> arm;

    friend class Arm;
public:

    Human(glm::vec3 pos, glm::vec3 rot);

    bool update(Scene &scene, float dt) override;

    void render(Scene &scene) override;
};

#endif //PPGSO_HUMAN_H
