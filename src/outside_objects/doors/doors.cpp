#include <shaders/test_vert_glsl.h>
#include <shaders/test_frag_glsl.h>
#include "src/scene.h"
#include "doors.h"

Doors::Doors(glm::vec3 pos) {
    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(phongo_vert_glsl, phongo_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("door.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("doors.obj");
    material = {{0.19225f,0.19225f,0.19225f},
                {0.50754f,0.50754f,0.50754f},{0.508273f,0.508273f,0.508273f},0.4};

    position = pos;
    scale = {3,3,3};
}


bool Doors::update(Scene &scene, float dt) {
    if (scene.age >= 80) { animate(dt);}
    generateModelMatrix();
    return true;
}

void Doors::render(Scene &scene) {

    // NOTE: this object does not use camera, just renders the entire quad as is
    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);


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

    shader->setUniform("Transparency", 0.9f);
    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);
    shader->setUniform("CameraPosition", scene.camera->position);

    mesh->render();
}

// shared resources
std::unique_ptr<ppgso::Mesh> Doors::mesh;
std::unique_ptr<ppgso::Shader> Doors::shader;
std::unique_ptr<ppgso::Texture> Doors::texture;
