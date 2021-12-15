//
// Created by Administrator on 29/11/2021.
//

//
// Created by Administrator on 23/11/2021.
//
#include <shaders/phongo_vert_glsl.h>
#include <shaders/phongo_frag_glsl.h>

#include "src/scene.h"
#include "tumbleweed.h"

Tumbleweed::Tumbleweed(glm::vec3 pos) {
    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(phongo_vert_glsl, phongo_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("tumble.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("tumble.obj");

    scale = {0.25, 0.25, 0.25};
    position = pos;
    position.y += 0.5;

    material = {{0.05f,0.05f,0.05f},
                {0.4f,0.5f,0.4f},{0.7f,0.7f,0.7f},48};

    bounding_box[0] = glm::vec3{-2.5,-2.5,-2.5}*scale;
    bounding_box[1] = glm::vec3{2.5,2.5,2.5}*scale;

    can_collide = true;
}

bool Tumbleweed::update(Scene &scene, float dt) {

    if(static_cast<int>(scene.age)%5 < rand()%3)
        position += scene.wind2*dt;

    if (!check_collision(position + scene.wind, scene)) {
        position += scene.wind*dt ;
        rotation.y -= 0.1;
    }
    else {
        rotation.y -= 0.006;
    }
    if (!check_collision(position + scene.gravity, scene)) {
        //s(t) = a*t*t*0.5f + v0*t + s0
        position += momentum*dt + scene.gravity*dt*dt*0.5f;
        //v = v0 + v*t
        momentum += scene.gravity*dt;
    }
    else {
        momentum.y = 0;
    }

    generateModelMatrix();
    return true;

}

void Tumbleweed::render(Scene &scene) {

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

    shader->setUniform("Transparency", 1.0f);
    // render mesh
    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);
    shader->setUniform("SceneAge", scene.age);
    shader->setUniform("CameraPosition", scene.camera->position);

    mesh->render();
}



// shared resources
std::unique_ptr<ppgso::Mesh> Tumbleweed::mesh;
std::unique_ptr<ppgso::Shader> Tumbleweed::shader;
std::unique_ptr<ppgso::Texture> Tumbleweed::texture;

