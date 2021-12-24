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
    if (initial_color_index == 0)
        animate=false;
    turnOn=turn_on_time;

}

bool ColorBulb::update(Scene &scene, float dt) {

    if (scene.age >= turnOn)
    {
        isActive = true;
    }

    if (animate)
    {
        int switch_color = static_cast<int>(scene.age) % 4 ;
        ambient = {colorLights[switch_color].x * 0.1, colorLights[switch_color].y * 0.1, colorLights[switch_color].z * 0.1};
        diffuse = {colorLights[switch_color].x,  colorLights[switch_color].y,  colorLights[switch_color].z};
        specular = {colorLights[switch_color].x,  colorLights[switch_color].y,  colorLights[switch_color].z};
    }


    return true;
}
