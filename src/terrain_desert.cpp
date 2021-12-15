//
// Created by Administrator on 23/11/2021.
//
#include <shaders/texture_vert_glsl.h>
#include <shaders/texture_frag_glsl.h>
#include <shaders/phongo_vert_glsl.h>
#include <shaders/phongo_frag_glsl.h>

#include "scene.h"

#include "terrain_desert.h"

terrain_desert::terrain_desert() {
    material = {{0.19225f,0.19225f,0.19225f},
                {0.80754f,0.80754f,0.50754f},{0.508273f,0.508273f,0.508273f},12};


    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(phongo_vert_glsl, phongo_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("sand.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("plane.obj");

    scale = {10,1,10};
    position = {0,0,0};
    bounding_box[0] = glm::vec3{-22,0,-21}*scale;
    bounding_box[1] = glm::vec3{22,0,21}*scale;
    can_collide = true;
}

bool terrain_desert::update(Scene &scene, float dt) {
    generateModelMatrix();
    return true;
}

void terrain_desert::render(Scene &scene) {

    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);
    shader->setUniform("isTerrain",1);
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
    int lights_count = 0;
    auto j = std::begin(scene.lightSources);
    while (j != std::end(scene.lightSources)) {
        if (scene.lightSources[i]->isActive) {
            std::string number = std::to_string(i);
            shader->setUniform("pointLights[" + number + "].position", scene.lightSources[i]->position);
            shader->setUniform("pointLights[" + number + "].ambient", scene.lightSources[i]->ambient);
            shader->setUniform("pointLights[" + number + "].specular", scene.lightSources[i]->specular);
            shader->setUniform("pointLights[" + number + "].diffuse", scene.lightSources[i]->diffuse);
            shader->setUniform("pointLights[" + number + "].constant", scene.lightSources[i]->constant);
            shader->setUniform("pointLights[" + number + "].linear", scene.lightSources[i]->linear);
            shader->setUniform("pointLights[" + number + "].quadratic", scene.lightSources[i]->quadratic);
            lights_count++;
        }
        ++j;
        ++i;
    }

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
}

// shared resources
std::unique_ptr<ppgso::Mesh> terrain_desert::mesh;
std::unique_ptr<ppgso::Shader> terrain_desert::shader;
std::unique_ptr<ppgso::Texture> terrain_desert::texture;