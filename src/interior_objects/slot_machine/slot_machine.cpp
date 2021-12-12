//
// Created by Administrator on 06/12/2021.
//
//
// Created by Administrator on 27/11/2021.
//

//
// Created by Administrator on 23/11/2021.
//
#include <shaders/texture_vert_glsl.h>
#include <shaders/texture_frag_glsl.h>
#include <glm/gtx/euler_angles.hpp>

#include "src/scene.h"
#include "slot_machine.h"

SlotMachine::SlotMachine() {
    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(texture_vert_glsl, texture_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("automat.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("automat.obj");

    position = {0,0,0};
    rotation = {0,0,2.2};

    screen = std::make_unique<Screen>(position + glm::vec3 {0,0,-0.01}, rotation, scale);
}

bool SlotMachine::update(Scene &scene, float dt) {
    screen->update(scene,dt);
    generateModelMatrix();
    return true;
}

void SlotMachine::render(Scene &scene) {
    // NOTE: this object does not use camera, just renders the entire quad as is
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

    screen->render(scene);
}

// shared resources
std::unique_ptr<ppgso::Mesh> SlotMachine::mesh;
std::unique_ptr<ppgso::Shader> SlotMachine::shader;
std::unique_ptr<ppgso::Texture> SlotMachine::texture;
