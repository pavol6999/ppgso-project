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
#include <shaders/phongo_vert_glsl.h>

#include "src/scene.h"
#include "building.h"

Building::Building() {

    material = {{0.19225f,0.19225f,0.19225f},
                         {0.50754f,0.50754f,0.50754f},{0.508273f,0.508273f,0.508273f},0.4};

    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(phongo_vert_glsl, phongo_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("casino.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("casino.obj");

    position = {0,0,0};
    scale = {3,3,3};

    bounding_box[0] = {-3.*scale.x,0.*scale.y,-2.*scale.z};
    bounding_box[1] = {3.*scale.x,2.*scale.y,2.3*scale.z};
    can_collide = true;
}

bool Building::update(Scene &scene, float dt) {
    generateModelMatrix();
    return true;
}

void Building::render(Scene &scene) {




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



    int lightCount = scene.lightSources.size();
    int i = 0;
    shader->setUniform("lightsCount",lightCount);
    auto j = std::begin(scene.lightSources);
    while (j != std::end(scene.lightSources)) {

        std::string number = std::to_string(i);                                     ;
        shader->setUniform("pointLights["+number+"].position",scene.lightSources[i]->position);
        shader->setUniform("pointLights["+number+"].ambient",scene.lightSources[i]->ambient);
        shader->setUniform("pointLights["+number+"].specular",scene.lightSources[i]->specular);
        shader->setUniform("pointLights["+number+"].diffuse",scene.lightSources[i]->diffuse);
        shader->setUniform("pointLights["+number+"].constant",scene.lightSources[i]->constant);
        shader->setUniform("pointLights["+number+"].linear",scene.lightSources[i]->linear);
        shader->setUniform("pointLights["+number+"].quadratic",scene.lightSources[i]->quadratic);
        ++j;
        ++i;
    }

    int spotlightsCount = scene.spotlights.size();
    int k = 0;
    shader->setUniform("spotlightsCount",spotlightsCount);
    auto l = std::begin(scene.spotlights);
    while (l != std::end(scene.spotlights)) {

        std::string number = std::to_string(k);

        shader->setUniform("spotLights["+number+"].position",scene.spotlights[k]->position);

        shader->setUniform("spotLights["+number+"].ambient",scene.spotlights[k]->ambient);
        shader->setUniform("spotLights["+number+"].specular",scene.spotlights[k]->specular);
        shader->setUniform("spotLights["+number+"].diffuse",scene.spotlights[k]->diffuse);
        shader->setUniform("spotLights["+number+"].constant",scene.spotlights[k]->constant);
        shader->setUniform("spotLights["+number+"].linear",scene.spotlights[k]->linear);
        shader->setUniform("spotLights["+number+"].outerCutOff",glm::cos(glm::radians(30.0f)));
        shader->setUniform("spotLights["+number+"].cutOff",glm::cos(glm::radians(25.f)));
        shader->setUniform("spotLights["+number+"].direction",scene.spotlights[k]->center);
        shader->setUniform("spotLights["+number+"].quadratic",scene.spotlights[k]->quadratic);
        ++l;
        ++k;
    }

    shader->setUniform("Transparency", 1.0f);
    // render mesh
    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);
    shader->setUniform("SceneAge", scene.age);
    shader->setUniform("CameraPosition", scene.camera->position);

    mesh->render();
}

// shared resources
std::unique_ptr<ppgso::Mesh> Building::mesh;
std::unique_ptr<ppgso::Shader> Building::shader;
std::unique_ptr<ppgso::Texture> Building::texture;