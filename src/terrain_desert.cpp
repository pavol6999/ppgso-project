//
// Created by Administrator on 23/11/2021.
//
#include <shaders/texture_vert_glsl.h>
#include <shaders/texture_frag_glsl.h>
#include <shaders/test_vert_glsl.h>
#include <shaders/test_frag_glsl.h>

#include "scene.h"

#include "terrain_desert.h"

terrain_desert::terrain_desert() {
    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(test_vert_glsl, test_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("sand.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("plane.obj");

    scale = {10,1,10};
    position = {0,0,0};
}

bool terrain_desert::update(Scene &scene, float dt) {
    generateModelMatrix();
    return true;
}

void terrain_desert::render(Scene &scene) {

    // NOTE: this object does not use camera, just renders the entire quad as is
    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    // render mesh
    shader->setUniform("objectColor", {0.3f, 0.6f, 0.f});
    shader->setUniform("lightColor",  {1.0f, 1.0f, 1.0f});
    shader->setUniform("lightPos", {0,100,0});
    shader->setUniform("Transparency", 1.0f);
    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);
    shader->setUniform("CameraPosition", scene.camera->position);

    mesh->render();
}

// shared resources
std::unique_ptr<ppgso::Mesh> terrain_desert::mesh;
std::unique_ptr<ppgso::Shader> terrain_desert::shader;
std::unique_ptr<ppgso::Texture> terrain_desert::texture;