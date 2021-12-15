//
// Created by Administrator on 10/12/2021.
//

#include <shaders/texture_vert_glsl.h>
#include <shaders/texture_frag_glsl.h>
#include <glm/gtx/euler_angles.hpp>

#include "src/scene.h"
#include "human.h"

Human::Human(glm::vec3 pos, glm::vec3 rot) {
    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(texture_vert_glsl, texture_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("human.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("human.obj");

    position = pos;
    rotation = rot;
    arm = std::make_unique<Arm>(*this);
}

bool Human::update(Scene &scene, float dt) {
    arm->update(scene,dt);
    generateModelMatrix();
    return true;
}

void Human::render(Scene &scene) {
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

    arm->render(scene);
}

// shared resources
std::unique_ptr<ppgso::Mesh> Human::mesh;
std::unique_ptr<ppgso::Shader> Human::shader;
std::unique_ptr<ppgso::Texture> Human::texture;

