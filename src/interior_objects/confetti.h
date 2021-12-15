//
// Created by Administrator on 14/12/2021.
//

#ifndef PPGSO_CONFETTI_H
#define PPGSO_CONFETTI_H

#include "src/scene.h"
#include "src/object.h"

#include <shaders/phongo_vert_glsl.h>
#include <shaders/phongo_frag_glsl.h>

class Confetti : public  Object {
    // Static resources shared between all particles
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture;
    
    const std::vector<std::string> tex = {"red.bmp", "blue.bmp", "green.bmp"};

    float mass = 0.01;

public:
    Confetti(glm::vec3 p, int c);

    bool update(Scene &scene, float dt);

    void render(Scene& scene);
};
#endif //PPGSO_CONFETTI_H
