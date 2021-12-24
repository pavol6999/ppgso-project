#include "sun.h"
#include <src/utilities/utils.h>
bool Sun::update(Scene &scene, float dt) {

    if (scene.age > 45 && position.x != -100 && position.z != -100)
    {
        position.x -= 2;
        position.z -= 2;

    }
    if (scene.age > 53) {
        ambient = {colorLights[1].x * 0.1, colorLights[1].y * 0.1, colorLights[1].z * 0.1};
        diffuse = {colorLights[1].x, colorLights[1].y, colorLights[1].z};
        specular = {colorLights[1].x, colorLights[1].y, colorLights[1].z};
    }

    return true;
}

Sun::Sun(int id, glm::vec3 pos) {

    colorLights = {
            glm::vec3(1.f, 1.f, 1.f),
            glm::vec3(0.0f, 0.0f, 0.8f),
            glm::vec3(1.0f, 1.0, 0.0),
            glm::vec3(0.2f, 0.2f, 1.0f)
    };
    ambient = {colorLights[0].x * 0.1, colorLights[0].y * 0.1, colorLights[0].z * 0.1};
    diffuse = {colorLights[0].x,  colorLights[0].y,  colorLights[0].z};
    specular = {colorLights[0].x,  colorLights[0].y,  colorLights[0].z};
    position=pos;
}
