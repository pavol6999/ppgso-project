//
// Created by Administrator on 30/11/2021.
//
#include <shaders/texture_vert_glsl.h>
#include <shaders/texture_frag_glsl.h>

#include "src/scene.h"
#include "doors.h"

Doors::Doors(glm::vec3 pos) {
    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(texture_vert_glsl, texture_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("door.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("doors.obj");

    position = pos;
    scale = {3,3,3};
}


bool Doors::update(Scene &scene, float dt) {
    if (scene.age >= 10) { animate(dt);}
    generateModelMatrix();
    return true;
}

void Doors::render(Scene &scene) {

    // NOTE: this object does not use camera, just renders the entire quad as is
    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    // render mesh
    shader->setUniform("objectColor", {0.3f, 0.6f, 0.f});
    shader->setUniform("lightColor",  {1.0f, 1.0f, 1.0f});
    shader->setUniform("lightPos",  scene.camera->position);
    shader->setUniform("Transparency", {0.5,0.5,0.5});
    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);
    shader->setUniform("CameraPosition", scene.camera->position);

    mesh->render();
}

// shared resources
std::unique_ptr<ppgso::Mesh> Doors::mesh;
std::unique_ptr<ppgso::Shader> Doors::shader;
std::unique_ptr<ppgso::Texture> Doors::texture;
