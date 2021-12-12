//
// Created by Administrator on 07/12/2021.
//
//
// Created by Administrator on 06/12/2021.
//
//
// Created by Administrator on 27/11/2021.
//

//
// Created by Administrator on 23/11/2021.
//
#include <shaders/test_vert_glsl.h>
#include <shaders/test_frag_glsl.h>
#include <glm/gtx/euler_angles.hpp>

#include "src/scene.h"
#include "roulette_table.h"

RouletteTable::RouletteTable(glm::vec3 pos, glm::vec3 rot) {
    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(test_vert_glsl, test_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("table_tex.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("table.obj");

    position = pos;
    rotation = rot;
    scale = {0.25,0.25,0.25};
    wheel = std::make_unique<RouletteWheel>(position, rotation, scale);
}

bool RouletteTable::update(Scene &scene, float dt) {
    wheel->update(scene,dt);
    generateModelMatrix();
    return true;
}

void RouletteTable::render(Scene &scene) {
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

    wheel->render(scene);
}

// shared resources
std::unique_ptr<ppgso::Mesh> RouletteTable::mesh;
std::unique_ptr<ppgso::Shader> RouletteTable::shader;
std::unique_ptr<ppgso::Texture> RouletteTable::texture;

