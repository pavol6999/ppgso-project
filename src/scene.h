#ifndef _PPGSO_SCENE_H
#define _PPGSO_SCENE_H

#include <memory>
#include <map>
#include <list>
#include <string>

#include "scene_window.h"

//#include "camera.h"
//
class SceneWindow;

/*
 * Scene is an object that will aggregate all scene related data
 * Objects are stored in a list of objects
 * Keyboard and Mouse states are stored in a map and struct
 */
class Scene {
public:

    Scene(SceneWindow &window) : window(window) {}

    /*!
     * Update all objects in the scene
     * @param time
     */
    virtual void update(float time) = 0;

    /*!
     * Render all objects in the scene
     */
    virtual void render() = 0;

    SceneWindow &window;

    glm::vec3 bgColor = {0, 0, 0};

    // Camera object
    //std::unique_ptr<Camera> camera;

    // All objects to be rendered in scene
    //std::list< std::unique_ptr<Object> > objects;
};

#endif // _PPGSO_SCENE_H
