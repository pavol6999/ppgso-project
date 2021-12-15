//
// Created by FIIT STU on 12/11/2021.
//

#include "sun.h"

bool Sun::update(Scene &scene, float dt) {

    if (scene.age > 4.9)
    {
        return false;
        ambient = {colorLights[3].x * 0.1, colorLights[3].y * 0.1, colorLights[3].z * 0.1};
        diffuse = {colorLights[3].x,  colorLights[3].y,  colorLights[3].z};
        specular = {colorLights[3].x,  colorLights[3].y,  colorLights[3].z};
    }


    return true;
}

Sun::Sun(int id, glm::vec3 pos) {

    colorLights = {
            glm::vec3(1.f, 1.f, 1.f),
            glm::vec3(1.0f, 0.0f, 0.0f),
            glm::vec3(1.0f, 1.0, 0.0),
            glm::vec3(0.2f, 0.2f, 1.0f)
    };
    ambient = {colorLights[0].x * 0.1, colorLights[0].y * 0.1, colorLights[0].z * 0.1};
    diffuse = {colorLights[0].x,  colorLights[0].y,  colorLights[0].z};
    specular = {colorLights[0].x,  colorLights[0].y,  colorLights[0].z};
    position=pos;
}
