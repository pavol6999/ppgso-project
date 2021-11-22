//
// Created by FIIT STU on 11/19/2021.
//

#include "scene_window.h"
#include "scene.h"
#include <ppgso/ppgso.h>
#include <string>

void SceneWindow::createIndoorScene() {
    //auto indoorScene = std::make_shared<Scene>(*this);
   //scenes.push_back(indoorScene);

   //scene.objects.clear();

    // Create a camera
//    auto camera = std::make_unique<Camera>(60.0f, 1.0f, 0.1f, 100.0f);
//    camera->position.z = -15.0f;
//    scene.camera = move(camera);


}

void SceneWindow::createOutdoorScene() {
//    auto scene = std::make_shared<Scene>(*this);
//    scenes.push_back(scene);
//    scene.objects.clear();

    // Create a camera
//    auto camera = std::make_unique<Camera>(60.0f, 1.0f, 0.1f, 100.0f);
//    camera->position.z = -15.0f;
//    scene.camera = move(camera);


    }


SceneWindow::SceneWindow(const int width, const int height) : Window{"kokot pica", width, height}
{

    // Initialize OpenGL state
    // Enable Z-buffer
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    // Enable polygon culling
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

    createOutdoorScene();
    createIndoorScene();
    activeScene = 2;
}

/*!
 * Window update implementation that will be called automatically from pollEvents
 */
void SceneWindow::onIdle() {
    // Track time
    //static auto time = (float) glfwGetTime();

    // Compute time delta
    //float dt = animate ? (float) glfwGetTime() - time : 0;

    //time = (float) glfwGetTime();

    // Set gray background
    glClearColor(.5f, .5f, .5f, 0);
    // Clear depth and color buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//    // Update and render all objects
//    scene.update(dt);
//    scene.render();
}
