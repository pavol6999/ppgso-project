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

SlotMachine::SlotMachine(glm::vec3 pos, glm::vec3 rot) {
    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(phongo_vert_glsl, phongo_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("automat.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("automat.obj");
    material = {{0.19225f,0.19225f,0.19225f},
                {0.50754f,0.50754f,0.50754f},{0.508273f,0.508273f,0.508273f},0.4};

    position = pos;
    rotation = rot;

    screen = std::make_unique<Screen>(position + glm::vec3 {0,0,0}, rotation, scale);
}

bool SlotMachine::update(Scene &scene, float dt) {
    screen->update(scene,dt);
    generateModelMatrix();
    return true;
}

void SlotMachine::render(Scene &scene) {
    // use camera
    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);
    shader->setUniform("isTerrain",0);
    shader->setUniform("material.ambient", material.ambient);
    shader->setUniform("material.diffuse", material.diffuse);
    shader->setUniform("material.specular", material.specular);
    shader->setUniform("material.shininess", material.shininess);


    if (scene.sun)
    {
        shader->setUniform("sun.position", scene.sun->position);
        shader->setUniform("sun.ambient",scene.sun->ambient);
        shader->setUniform("sun.specular",scene.sun->diffuse);
        shader->setUniform("sun.diffuse",scene.sun->specular);
    }


    int i = 0;
    int lightsCount = 0;
    auto j = std::begin(scene.lightSources);
    while (j != std::end(scene.lightSources)) {
        if (scene.lightSources[i]->isActive) {
            std::string number = std::to_string(i);
            shader->setUniform("pointLights["+number+"].position",scene.lightSources[i]->position);
            shader->setUniform("pointLights["+number+"].ambient",scene.lightSources[i]->ambient);
            shader->setUniform("pointLights["+number+"].specular",scene.lightSources[i]->specular);
            shader->setUniform("pointLights["+number+"].diffuse",scene.lightSources[i]->diffuse);
            shader->setUniform("pointLights["+number+"].constant",scene.lightSources[i]->constant);
            shader->setUniform("pointLights["+number+"].linear",scene.lightSources[i]->linear);
            shader->setUniform("pointLights["+number+"].quadratic",scene.lightSources[i]->quadratic);
            lightsCount++;
        }
        ++j;
        ++i;
    }
    shader->setUniform("lightsCount",lightsCount);
    int spotlightsCount = 0;
    int k = 0;

    auto l = std::begin(scene.spotlights);
    while (l != std::end(scene.spotlights)) {
        if (scene.spotlights[k]->isActive) {
            std::string number = std::to_string(k);

            shader->setUniform("spotLights["+number+"].position",scene.spotlights[k]->position);

            shader->setUniform("spotLights["+number+"].ambient",scene.spotlights[k]->ambient);
            shader->setUniform("spotLights["+number+"].specular",scene.spotlights[k]->specular);
            shader->setUniform("spotLights["+number+"].diffuse",scene.spotlights[k]->diffuse);
            shader->setUniform("spotLights["+number+"].constant",scene.spotlights[k]->constant);
            shader->setUniform("spotLights["+number+"].linear",scene.spotlights[k]->linear);
            shader->setUniform("spotLights["+number+"].outerCutOff",scene.spotlights[k]->outerCutOff);
            shader->setUniform("spotLights["+number+"].cutOff",scene.spotlights[k]->cutOff);
            shader->setUniform("spotLights["+number+"].direction",scene.spotlights[k]->center);
            shader->setUniform("spotLights["+number+"].quadratic",scene.spotlights[k]->quadratic);
            spotlightsCount++;
        }
        ++l;
        ++k;
    }
    shader->setUniform("spotlightsCount",spotlightsCount);


    shader->setUniform("Transparency", 1.0f);
    // render mesh
    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);
    shader->setUniform("SceneAge", scene.age);
    shader->setUniform("CameraPosition", scene.camera->position);

    mesh->render();

    screen->render(scene);
}

// shared resources
std::unique_ptr<ppgso::Mesh> SlotMachine::mesh;
std::unique_ptr<ppgso::Shader> SlotMachine::shader;
std::unique_ptr<ppgso::Texture> SlotMachine::texture;
