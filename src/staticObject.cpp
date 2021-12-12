//
// Created by FIIT STU on 11/30/2021.
//

#include "staticObject.h"
#include <shaders/texture_vert_glsl.h>
#include <shaders/texture_frag_glsl.h>
#include <shaders/phongo_frag_glsl.h>
#include <shaders/phongo_vert_glsl.h>
#include <GL/glew.h>

std::unique_ptr<ppgso::Mesh> StaticObject::mesh[num_obj];
std::unique_ptr<ppgso::Shader> StaticObject::shader;
std::unique_ptr<ppgso::Texture> StaticObject::texture[num_obj];
std::string StaticObject::texNames[num_obj] = {"cactus.bmp", "cactus.bmp","stone.bmp","rock.bmp"};
std::string StaticObject::meshNames[num_obj] = {"cactus.obj","cactus_long.obj","stone.obj", "rock.obj"};
std::vector<std::array<glm::vec3,2>> StaticObject::bounding_boxes = {
        {glm::vec3{0,0,-1}, glm::vec3{1,1,0}},
        {glm::vec3{0,0,-1}, glm::vec3{1,2,0}},
        {glm::vec3{-4.2, -4, -5.1}, glm::vec3{3.2, 3.1, 4}},
        {glm::vec3{-1.7, 0, -2}, glm::vec3{2.5,1.5,2}} };
const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

StaticObject::StaticObject(int obj_id, glm::vec3 position_new, glm::vec3 rotation_new = {0,0,0}, glm::vec3 scale_new = {1,1,1}) {
    this->obj_id = obj_id;
    if (!shader) shader = std::make_unique<ppgso::Shader>(phongo_vert_glsl, phongo_frag_glsl);
    if (!texture[obj_id]) texture[obj_id] = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP(texNames[obj_id]));
    if (!mesh[obj_id]) mesh[obj_id] = std::make_unique<ppgso::Mesh>(meshNames[obj_id]);

    position = position_new;
    rotation = rotation_new;
    scale = scale_new;
    if (obj_id == 0)
        material = {{0.05f,0.05f,0.05f},
                    {0.4f,0.5f,0.4f},{0.7f,0.7f,0.7f},48};

    if (obj_id == 1)
        material = {{0.05f,0.05f,0.05f},
                    {0.4f,0.5f,0.4f},{0.7f,0.7f,0.7f},48};
    if (obj_id == 2)
        material = {{0.08f,0.08f,0.08f},
                    {0.50f,0.50f,0.50f},{0.55f,0.55f,0.55f},32};

    if (obj_id == 3)
        material = {{0.1f,0.1f,0.1f},
                    {0.55f,0.55f,0.55f},{0.6f,0.6f,0.6f},24.4};


    bounding_box[0] = bounding_boxes[obj_id][0]*scale;
    bounding_box[1] = bounding_boxes[obj_id][1]*scale;
    can_collide = true;
}





bool StaticObject::update(Scene &scene, float dt) {
    generateModelMatrix();
    return true;
}



void StaticObject::render(Scene &scene) {

    //shader->setUniform("LightDirection", {0, 0, 0});
//
//
//    // use camera
//    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
//    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);
//
//    // render mesh
//    shader->setUniform("objectColor", {0.3f, 0.6f, 0.f});
//    shader->setUniform("lightColor",  {1.0f, 1.0f, 1.0f});
//    shader->setUniform("lightPos",  scene.camera->position);
//    shader->setUniform("Transparency", 1.0f);
//    shader->setUniform("ModelMatrix", modelMatrix);
//    shader->setUniform("Texture", *texture[obj_id]);
//    shader->setUniform("CameraPosition", scene.camera->position);
//
//
//    mesh[obj_id]->render();
    // use camera
    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    shader->setUniform("material.ambient", material.ambient);
    shader->setUniform("material.diffuse", material.diffuse);
    shader->setUniform("material.specular", material.specular);
    shader->setUniform("material.shininess", material.shininess);

    shader->setUniform("sun.position", scene.sun->position);
    shader->setUniform("sun.ambient",scene.sun->ambient);
    shader->setUniform("sun.specular",scene.sun->diffuse);
    shader->setUniform("sun.diffuse",scene.sun->specular);

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
    shader->setUniform("SceneAge", scene.age);
    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture[obj_id]);
    shader->setUniform("CameraPosition", scene.camera->position);

    mesh[obj_id]->render();




}




