//
// Created by Administrator on 23/11/2021.
//
#include <shaders/texture_vert_glsl.h>
#include <shaders/texture_frag_glsl.h>

#include "src/scene.h"
#include "skybox.h"

SkyBox::SkyBox() {
    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(texture_vert_glsl, texture_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("sky.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("skybox.obj");

    scale = {200,200,200};
}

SkyBox::SkyBox(glm::vec3 scale_new) {
    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(texture_vert_glsl, texture_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("sky.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("skybox.obj");

    scale = scale_new;
}

bool SkyBox::update(Scene &scene, float dt) {
    rotation.x += 0.005;
    generateModelMatrix();
    return true;
}

void SkyBox::render(Scene &scene) {

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
std::unique_ptr<ppgso::Mesh> SkyBox::mesh;
std::unique_ptr<ppgso::Shader> SkyBox::shader;
std::unique_ptr<ppgso::Texture> SkyBox::texture;