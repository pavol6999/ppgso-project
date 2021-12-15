//
// Created by Administrator on 14/12/2021.
//

#include "confetti.h"

Confetti::Confetti(glm::vec3 p, int c) {
    // First particle will initialize resources
    if (!shader) shader = std::make_unique<ppgso::Shader>(phongo_vert_glsl, phongo_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP(tex[c]));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("confetti.obj");

    position = p;

    scale = {0.25, 0.25, 0.25};
    rotation = {rand()*314/100.,rand()*314/100.,rand()*314/100.};
}

bool Confetti::update(Scene &scene, float dt) {
    position.y += -0.05;
    if (position.y < 0) return false;
    generateModelMatrix();
    return true;
}

void Confetti::render(Scene& scene){

    shader->setUniform("LightDirection", {0, 0, 0});


    // use camera
    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);



    // render mesh
    shader->setUniform("objectColor", {0.3f, 0.6f, 0.f});
    shader->setUniform("lightColor",  {1.0f, 1.0f, 1.0f});
    shader->setUniform("lightPos",  scene.camera->position);
    shader->setUniform("Transparency", 1.f);
    // render mesh
    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);
    shader->setUniform("CameraPosition", scene.camera->position);

    mesh->render();
}


// Static resources need to be instantiated outside of the class as they are globals
std::unique_ptr<ppgso::Mesh> Confetti::mesh;
std::unique_ptr<ppgso::Shader> Confetti::shader;
std::unique_ptr<ppgso::Texture> Confetti::texture;