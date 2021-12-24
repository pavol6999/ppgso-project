#pragma once

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <vector>


class Scene;

class Light {

public:


    glm::vec3 diffuse;
    glm::vec3 ambient;
    glm::vec3 specular;
    glm::vec3 position;
    bool isActive = false;
    float turnOn = -1.f;
    Light() = default;
    Light(const Light&) = default;
    Light(Light&&) = default;
    virtual ~Light() {};


    virtual bool update(Scene &scene, float dt) = 0;

};



