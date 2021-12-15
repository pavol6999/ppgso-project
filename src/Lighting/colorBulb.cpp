//
// Created by FIIT STU on 12/11/2021.
//

#include "colorBulb.h"
ColorBulb::ColorBulb(glm::vec3 pos, int initial_color_index, float turn_on_time) {

    colorLights = {
            glm::vec3(1.f, 1.f, 1.f),
            glm::vec3(0.0f, 0.8f, 0.6f),
            glm::vec3(1.0f, 1.0, 0.0),
            glm::vec3(0.2f, 0.2f, 1.0f)
    };
    ambient = {colorLights[initial_color_index].x * 0.1, colorLights[initial_color_index].y * 0.1, colorLights[initial_color_index].z * 0.1};
    diffuse = {colorLights[initial_color_index].x,  colorLights[initial_color_index].y,  colorLights[initial_color_index].z};
    specular = {colorLights[initial_color_index].x,  colorLights[initial_color_index].y,  colorLights[initial_color_index].z};
    position=pos;
    turnOn=turn_on_time;

}

bool ColorBulb::update(Scene &scene, float dt) {

    if (scene.age >= turnOn)
    {
        isActive = true;
    }

    int switch_color = static_cast<int>(scene.age) %  3;
    if (switch_color > 1)
    {
        int random_color = rand() % 4;
        ambient = {colorLights[random_color].x * 0.1, colorLights[random_color].y * 0.1, colorLights[random_color].z * 0.1};
        diffuse = {colorLights[random_color].x,  colorLights[random_color].y,  colorLights[random_color].z};
        specular = {colorLights[random_color].x,  colorLights[random_color].y,  colorLights[random_color].z};
    }



    return true;
}
