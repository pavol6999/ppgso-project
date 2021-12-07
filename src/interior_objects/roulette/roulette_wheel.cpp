//
// Created by Administrator on 07/12/2021.
//

#include <shaders/texture_vert_glsl.h>
#include <shaders/texture_frag_glsl.h>
#include <glm/gtx/euler_angles.hpp>

#include "src/scene.h"
#include "roulette_wheel.h"

RouletteWheel::RouletteWheel(glm::vec3 pos, glm::vec3 rot, glm::vec3 sc) {
    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(texture_vert_glsl, texture_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("roulette_Tex.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("wheel.obj");

    position = pos;
    rotation = rot;
    scale = sc;
    moving = std::make_unique<RouletteMoving>(position, rotation, scale);
}

bool RouletteWheel::update(Scene &scene, float dt) {
    moving->update(scene,dt);
    generateModelMatrix();
    return true;
}

void RouletteWheel::render(Scene &scene) {
    // NOTE: this object does not use camera, just renders the entire quad as is
    shader->setUniform("LightDirection", {0, 0, 0});


    // use camera
    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    // render mesh
    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);
    shader->setUniform("CameraPosition", scene.camera->position);

    mesh->render();

    moving->render(scene);
}

// shared resources
std::unique_ptr<ppgso::Mesh> RouletteWheel::mesh;
std::unique_ptr<ppgso::Shader> RouletteWheel::shader;
std::unique_ptr<ppgso::Texture> RouletteWheel::texture;

