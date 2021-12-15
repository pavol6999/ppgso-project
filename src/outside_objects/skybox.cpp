//
// Created by Administrator on 23/11/2021.
//
#include <shaders/texture_vert_glsl.h>
#include <shaders/texture_frag_glsl.h>
#include <shaders/phongo_vert_glsl.h>
#include <shaders/phongo_frag_glsl.h>

#include "src/scene.h"
#include "skybox.h"

SkyBox::SkyBox() {
    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(phongo_vert_glsl, phongo_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("sky.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("skybox.obj");
    material = {{0.329412f,0.329412f,0.329412f},
                {1.f,1.f,1.f},{0.f,0.f,0.f},0};

    scale = {200,200,200};
    rotation = {3.14, 0 ,0};
}

SkyBox::SkyBox(glm::vec3 scale_new) {
    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(phongo_vert_glsl, phongo_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("sky.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("skybox.obj");
    material = {{0.329412f,0.329412f,0.329412f},
                {1.f,1.f,1.f},{0.f,0.f,0.f},0};

    scale = scale_new;


    key_frames.push_back({{10,10,10}, {0,0,0}, {3.14, 0 ,0}});
    key_frames.push_back({{7,7,7}, {0,0,0}, {0, 0 ,0}});
    position = key_frames[0].position;
    rotation = key_frames[0].rotation;

}

bool SkyBox::update(Scene &scene, float dt) {
    if (scene.age >= 43) animate(dt);
    generateModelMatrix();
    return true;
}

void SkyBox::render(Scene &scene) {

    // NOTE: this object does not use camera, just renders the entire quad as is
//    shader->setUniform("LightDirection", {0, 0, 0});
//
//
//    // use camera
//    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
//    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);
//
//    // render mesh
//    shader->setUniform("Transparency", 1.0f);
//    shader->setUniform("ModelMatrix", modelMatrix);
//    shader->setUniform("Texture", *texture);
//    shader->setUniform("CameraPosition", scene.camera->position);
//
//    mesh->render();


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
    shader->setUniform("lightsCount",lights_count);
    shader->setUniform("Transparency", 1.0f);
    // render mesh
    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);
    shader->setUniform("SceneAge", scene.age);
    shader->setUniform("CameraPosition", scene.camera->position);

    mesh->render();
}

// shared resources
std::unique_ptr<ppgso::Mesh> SkyBox::mesh;
std::unique_ptr<ppgso::Shader> SkyBox::shader;
std::unique_ptr<ppgso::Texture> SkyBox::texture;