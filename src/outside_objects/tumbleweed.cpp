//
// Created by Administrator on 29/11/2021.
//

//
// Created by Administrator on 23/11/2021.
//
#include <shaders/texture_vert_glsl.h>
#include <shaders/texture_frag_glsl.h>

#include "src/scene.h"
#include "tumbleweed.h"

Tumbleweed::Tumbleweed() {
    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(texture_vert_glsl, texture_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("tumble.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("tumble.obj");

    scale = {0.25, 0.25, 0.25};
    position = { -5, 0.5, 10};

    bounding_box[0] = glm::vec3{-2.5,-2.5,-2.5}*scale;
    bounding_box[1] = glm::vec3{2.5,2.5,2.5}*scale;
    can_collide = true;
}

bool Tumbleweed::update(Scene &scene, float dt) {

    generateModelMatrix();
    return true;

}

void Tumbleweed::render(Scene &scene) {

    // NOTE: this object does not use camera, just renders the entire quad as is
    shader->setUniform("LightDirection", {0, 0, 0});

    // use camera
    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    // render mesh
    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);
    shader->setUniform("Transparency", 1.f);
    shader->setUniform("CameraPosition", scene.camera->position);

    mesh->render();
}



// shared resources
std::unique_ptr<ppgso::Mesh> Tumbleweed::mesh;
std::unique_ptr<ppgso::Shader> Tumbleweed::shader;
std::unique_ptr<ppgso::Texture> Tumbleweed::texture;

