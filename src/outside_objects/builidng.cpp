//
// Created by Administrator on 27/11/2021.
//

//
// Created by Administrator on 23/11/2021.
//
#include <shaders/texture_vert_glsl.h>
#include <shaders/texture_frag_glsl.h>
#include <glm/gtx/euler_angles.hpp>
#include <shaders/test_vert_glsl.h>
#include <shaders/test_frag_glsl.h>
#include <shaders/phongo_frag_glsl.h>

#include "src/scene.h"
#include "building.h"

Building::Building() {

    material = {{0.19225f,0.19225f,0.19225f},
                         {0.50754f,0.50754f,0.50754f},{0.508273f,0.508273f,0.508273f},0.4};

    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(test_vert_glsl, test_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("casino.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("casino.obj");

    position = {0,0,0};
    scale = {3,3,3};

}

bool Building::update(Scene &scene, float dt) {
    generateModelMatrix();
    return true;
}

void Building::render(Scene &scene) {

    // NOTE: this object does not use camera, just renders the entire quad as is
    shader->setUniform("LightDirection", {0, 0, 0});


    // use camera
    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    shader->setUniform("material.ambient", material.ambient);
    shader->setUniform("material.diffuse", material.diffuse);
    shader->setUniform("material.specular", material.specular);
    shader->setUniform("material.shininess", material.shininess);

    shader->setUniform("light.ambient", {0.2f, 0.2f, 0.2f});
    shader->setUniform("light.diffuse", {0.7f, 0.7f, 0.7f}); // darken diffuse light a bit
    shader->setUniform("light.specular", {1.0f, 1.0f, 1.0f});


    shader->setUniform("light.constant",  1.0f);
    shader->setUniform("light.linear",    0.09f);
    shader->setUniform("light.quadratic", 0.032f);

    // render mesh
    shader->setUniform("objectColor", {0.3f, 0.6f, 0.f});
    shader->setUniform("lightColor",  {1.0f, 1.0f, 1.0f});
    shader->setUniform("lightPos",  scene.camera->position);
    shader->setUniform("Transparency", 1.0f);
    // render mesh
    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);
    shader->setUniform("CameraPosition", scene.camera->position);

    mesh->render();
}

// shared resources
std::unique_ptr<ppgso::Mesh> Building::mesh;
std::unique_ptr<ppgso::Shader> Building::shader;
std::unique_ptr<ppgso::Texture> Building::texture;