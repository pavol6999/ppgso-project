//
// Created by FIIT STU on 12/11/2021.
//
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

    Light() = default;
    Light(const Light&) = default;
    Light(Light&&) = default;
    virtual ~Light() {};


    virtual bool update(Scene &scene, float dt) = 0;

};



