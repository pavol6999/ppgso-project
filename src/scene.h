#ifndef _PPGSO_SCENE_H
#define _PPGSO_SCENE_H

#include <memory>
#include <map>
#include <list>
#include <string>

#include "camera.h"
#include "object.h"


/*
 * Scene is an object that will aggregate all scene related data
 * Objects are stored in a list of objects
 */
class Scene {
public:
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

    // All objects to be rendered in scene
    std::list< std::unique_ptr<Object> > objects;
};

#endif // _PPGSO_SCENE_H
