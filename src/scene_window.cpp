//
// Created by FIIT STU on 11/19/2021.
//

#include "scene_window.h"
#include "skybox.h"
#include "building.h"
#include "tumbleweed.h"
#include "terrain_desert.h"
#include "staticObject.h"


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
    auto camera = std::make_unique<Camera>(60.0f, 1.0f, 0.1f, 250.0f);
    scene.camera = move(camera);

    // Add background
    scene.objects.push_back(std::make_unique<SkyBox>());

    scene.objects.push_back(std::make_unique<terrain_desert>());
    scene.objects.push_back(std::make_unique<Building>());

    glm::vec3 p = {0, 0, 10}; // floor
    glm::vec3 r = {0, 0, 0};
    glm::vec3 s = {1, 1, 1};
    auto obj = std::make_unique<StaticObject>(1, p, r, s);
    scene.objects.push_back(move(obj));

    for (int i = 0; i < 10; i++)
        scene.objects.push_back(std::make_unique<Tumbleweed>());

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

    // Set gray background

    glClearColor(.5f, .5f, .5f, 0);
    // Clear depth and color buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Update and render all objects
    scene.update(dt);
    scene.render();
}
