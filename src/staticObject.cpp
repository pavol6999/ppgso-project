//
// Created by FIIT STU on 11/30/2021.
//

#include "staticObject.h"
#include <shaders/texture_vert_glsl.h>
#include <shaders/texture_frag_glsl.h>
#include <shaders/test_frag_glsl.h>
#include <shaders/test_vert_glsl.h>

std::unique_ptr<ppgso::Mesh> StaticObject::mesh[num_obj];
std::unique_ptr<ppgso::Shader> StaticObject::shader;
std::unique_ptr<ppgso::Texture> StaticObject::texture[num_obj];
char *StaticObject::texNames[num_obj] = {"cactus.bmp", "cactus.bmp"};
char *StaticObject::meshNames[num_obj] = {"cactus.obj","cactus_long.obj"};


StaticObject::StaticObject(int obj_id, glm::vec3 position_new, glm::vec3 rotation_new, glm::vec3 scale_new) {
    this->obj_id = obj_id;
    if (!shader) shader = std::make_unique<ppgso::Shader>(texture_vert_glsl, texture_frag_glsl);
    if (!texture[obj_id]) texture[obj_id] = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP(texNames[obj_id]));
    if (!mesh[obj_id]) mesh[obj_id] = std::make_unique<ppgso::Mesh>(meshNames[obj_id]);

    position = position_new;
    rotation = rotation_new;
    scale = scale_new;

}

bool StaticObject::update(Scene &scene, float dt) {
    generateModelMatrix();
    return true;
}



void StaticObject::render(Scene &scene) {
    shader->setUniform("LightDirection", {0, 0, 0});


    // use camera
    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    // render mesh
    shader->setUniform("objectColor", {0.3f, 0.6f, 0.f});
    shader->setUniform("lightColor",  {1.0f, 1.0f, 1.0f});


    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture[obj_id]);
    shader->setUniform("CameraPosition", scene.camera->position);

    mesh[obj_id]->render();
}



