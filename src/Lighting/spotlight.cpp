//
// Created by FIIT STU on 12/12/2021.
//

#include "spotlight.h"
#include <glm/glm.hpp>
bool Spotlight::update(Scene &scene, float dt) {
    if (scene.age >= turnOn && scene.age <= 85 )
    {
        isActive = true;
    }
    if (scene.age >= 85)
        return false;

    return true;
}

Spotlight::Spotlight(glm::vec3 pos, glm::vec3 dir, int initial_color_index, float turn_on_time ) {
    colorLights = {
            glm::vec3(0.f, 1.f, 0.f),
            glm::vec3(1.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 1.0f),
            glm::vec3(0.2f, 0.2f, 1.0f)
    };
    position=pos;
    ambient = {colorLights[initial_color_index].x * 0.1, colorLights[initial_color_index].y * 0.1, colorLights[initial_color_index].z * 0.1};
    diffuse = {colorLights[initial_color_index].x,  colorLights[initial_color_index].y,  colorLights[initial_color_index].z};
    specular = {colorLights[initial_color_index].x,  colorLights[initial_color_index].y,  colorLights[initial_color_index].z};
    center = dir - pos;
    initial_center = dir - pos;
    turnOn=turn_on_time;




}

