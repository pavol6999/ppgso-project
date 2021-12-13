//
// Created by FIIT STU on 12/11/2021.
//

#include "colorBulb.h"
ColorBulb::ColorBulb(glm::vec3 pos, int initial_color_index) {

    colorLights = {
            glm::vec3(1.f, 1.f, 1.f),
            glm::vec3(1.0f, 0.0f, 0.0f),
            glm::vec3(1.0f, 1.0, 0.0),
            glm::vec3(0.2f, 0.2f, 1.0f)
    };
    ambient = {colorLights[initial_color_index].x * 0.1, colorLights[initial_color_index].y * 0.1, colorLights[initial_color_index].z * 0.1};
    diffuse = {colorLights[initial_color_index].x,  colorLights[initial_color_index].y,  colorLights[initial_color_index].z};
    specular = {colorLights[initial_color_index].x,  colorLights[initial_color_index].y,  colorLights[initial_color_index].z};
    position=pos;

}

bool ColorBulb::update(Scene &scene, float dt) {

    int color = rand() % 4;
    ambient = {colorLights[color].x * 0.1, colorLights[color].y * 0.1, colorLights[color].z * 0.1};
    diffuse = {colorLights[color].x,  colorLights[color].y,  colorLights[color].z};
    specular = {colorLights[color].x,  colorLights[color].y,  colorLights[color].z};
    return true;
}
