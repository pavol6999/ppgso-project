//
// Created by Administrator on 30/11/2021.
//
#include <shaders/texture_vert_glsl.h>
#include <shaders/texture_frag_glsl.h>

#include "scene.h"
#include "doors.h"

Doors::Doors(glm::vec3 pos) {
    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(texture_vert_glsl, texture_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("door.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("doors.obj");

    position = pos;
    scale = {3,3,3};
}

void Doors::animate(float dt) {
    if (current_key == key_frames.size() - 1) {
        position = key_frames[current_key].position;
        rotation = key_frames[current_key].rotation;
        scale = key_frames[current_key].scale;
        return;
    }

    position += (dt*(key_frames[current_key + 1].position - key_frames[current_key].position))/key_frames[current_key].duration;
    rotation += (dt*(key_frames[current_key + 1].rotation - key_frames[current_key].rotation))/key_frames[current_key].duration;
    scale += (dt*(key_frames[current_key + 1].rotation - key_frames[current_key].rotation))/key_frames[current_key].duration;

    key_frames[current_key].age += dt;

    if (key_frames[current_key].age >= key_frames[current_key].duration.x) {
        current_key++;
    }
}

bool Doors::update(Scene &scene, float dt) {
    if (scene.age >= 10) { animate(dt);}
    generateModelMatrix();
    return true;
}

void Doors::render(Scene &scene) {

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
}

// shared resources
std::unique_ptr<ppgso::Mesh> Doors::mesh;
std::unique_ptr<ppgso::Shader> Doors::shader;
std::unique_ptr<ppgso::Texture> Doors::texture;
