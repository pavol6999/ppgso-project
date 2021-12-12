#ifndef _PPGSO_SCENE_H
#define _PPGSO_SCENE_H

#include <memory>
#include <map>
#include <list>
#include <string>
#include "src/Lighting/sun.h"
#include "src/Lighting/colorBulb.h"
#include "src/Lighting/spotlight.h"
#include "camera.h"
#include "object.h"
#include "src/Lighting/Light.h"

class Sun;
class ColorBulb;
/*
 * Scene is an object that will aggregate all scene related data
 * Objects are stored in a list of objects
 */
class Scene {
public:
    float near_plane = 1.0f, far_plane = 7.5f;
    glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
    glm::mat4 lightView = glm::lookAt(glm::vec3(-2.0f, 4.0f, -1.0f),
                                      glm::vec3( 0.0f, 0.0f,  0.0f),
                                      glm::vec3( 0.0f, 1.0f,  0.0f));
    glm::mat4 lightSpaceMatrix = lightProjection * lightView;

    glm::vec3 wind = {0.1,0,0};
    glm::vec3 gravity = {0,-0.1,0};

    float age = 0;
/*!
     * Update all objects in the scene
     * @param time
     */
    virtual void update(float time);

    /*!
     * Render all objects in the scene
     */
    virtual void render();

    glm::vec3 bgColor = {0, 0, 0};

    // Camera object
    std::unique_ptr<Camera> camera;
    std::vector<std::unique_ptr<Spotlight>> spotlights;
    std::vector<std::unique_ptr<ColorBulb>> lightSources;
    std::unique_ptr<Sun> sun;
    // All objects to be rendered in scene
    std::list<std::unique_ptr<Object>> objects;
};

#endif // _PPGSO_SCENE_H
