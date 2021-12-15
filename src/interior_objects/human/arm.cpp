//
// Created by Administrator on 10/12/2021.
//

#include <shaders/texture_vert_glsl.h>
#include <shaders/texture_frag_glsl.h>
#include <glm/gtx/euler_angles.hpp>

#include "src/scene.h"
#include "arm.h"

Arm::Arm(Human &human): human(human){
    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(texture_vert_glsl, texture_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("arm.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("arm.obj");

    rotation.x = -0.4;
}

bool Arm::update(Scene &scene, float dt) {
    rotation.x += cos(age*3)/50;
    age += dt;
    modelMatrix =
            glm::translate(glm::mat4(1.0f), position + human.position)
            * glm::orientate4(rotation + human.rotation)
            * glm::scale(glm::mat4(1.0f), human.scale);
    return true;
}

void Arm::render(Scene &scene) {
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
std::unique_ptr<ppgso::Mesh> Arm::mesh;
std::unique_ptr<ppgso::Shader> Arm::shader;
std::unique_ptr<ppgso::Texture> Arm::texture;

