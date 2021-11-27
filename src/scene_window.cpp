//
// Created by FIIT STU on 11/19/2021.
//

#include "scene_window.h"
#include "skybox.h"


//void SceneWindow::createIndoorScene() {
    //auto indoorScene = std::make_shared<Scene>(*this);
   //scenes.push_back(indoorScene);

   //scene.objects.clear();

    // Create a camera
//    auto camera = std::make_unique<Camera>(60.0f, 1.0f, 0.1f, 100.0f);
//    camera->position.z = -15.0f;
//    scene.camera = move(camera);


void SceneWindow::createOutdoorScene() {
    scene.objects.clear();

    // Create a camera
    auto camera = std::make_unique<Camera>(60.0f, 1.0f, 0.1f, 1000.0f);
    camera->position.z = 15.0f;

    scene.camera = move(camera);

    //scene.camera->viewMatrix = translate(glm::mat4{1.0f}, {0.0f, 0.0f, 0.f});

    // Add space background
    scene.objects.push_back(std::make_unique<SkyBox>());
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
}

/*!
 * Window update implementation that will be called automatically from pollEvents
 */
void SceneWindow::onIdle() {
    // Track time
    static auto time = (float) glfwGetTime();

    // Compute time delta
    float dt = (float) glfwGetTime() - time;

    //time = (float) glfwGetTime();

    // Set gray background

    glClearColor(.5f, .5f, .5f, 0);
    // Clear depth and color buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Update and render all objects
    scene.update(dt);
    scene.render();
}
