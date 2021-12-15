//
// Created by Administrator on 07/12/2021.
//

#include <shaders/texture_vert_glsl.h>
#include <shaders/texture_frag_glsl.h>
#include <glm/gtx/euler_angles.hpp>

#include "src/scene.h"
#include "roulette_wheel.h"

RouletteWheel::RouletteWheel(RouletteTable &table): table(table){
    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(texture_vert_glsl, texture_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("roulette_Tex.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("wheel.obj");

    moving = std::make_unique<RouletteMoving>(*this);
}

bool RouletteWheel::update(Scene &scene, float dt) {
    moving->update(scene,dt);
    modelMatrix =
            glm::translate(glm::mat4(1.0f), position + table.position)
            * glm::orientate4(rotation + table.rotation)
            * glm::scale(glm::mat4(1.0f), table.scale);
    return true;
}

void RouletteWheel::render(Scene &scene) {
    // NOTE: this object does not use camera, just renders the entire quad as is
    shader->setUniform("LightDirection", {0, 0, 0});


    // use camera
    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);
    shader->setUniform("isTerrain",0);
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

    moving->render(scene);
}

// shared resources
std::unique_ptr<ppgso::Mesh> RouletteWheel::mesh;
std::unique_ptr<ppgso::Shader> RouletteWheel::shader;
std::unique_ptr<ppgso::Texture> RouletteWheel::texture;

