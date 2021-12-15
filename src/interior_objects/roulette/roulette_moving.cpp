//
// Created by Administrator on 07/12/2021.
//

#include <shaders/texture_vert_glsl.h>
#include <shaders/texture_frag_glsl.h>
#include <glm/gtx/euler_angles.hpp>

#include "src/scene.h"
#include "roulette_moving.h"

RouletteMoving::RouletteMoving(RouletteWheel &wheel) : wheel(wheel){
    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(texture_vert_glsl, texture_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("roulette.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("moving.obj");

    scale = {0.25,0.25,0.25};
}

bool RouletteMoving::update(Scene &scene, float dt) {
    rotation.z += 0.1;
    modelMatrix =
            glm::translate(glm::mat4(1.0f), position + wheel.position + wheel.table.position)
            * glm::orientate4(rotation + wheel.rotation + wheel.table.rotation)
            * glm::scale(glm::mat4(1.0f), wheel.table.scale);
    return true;
}

void RouletteMoving::render(Scene &scene) {
    // NOTE: this object does not use camera, just renders the entire quad as is
    shader->setUniform("LightDirection", {0, 0, 0});

    shader->setUniform("isTerrain",0);
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
// shared resources
std::unique_ptr<ppgso::Mesh> RouletteMoving::mesh;
std::unique_ptr<ppgso::Shader> RouletteMoving::shader;
std::unique_ptr<ppgso::Texture> RouletteMoving::texture;

