//
// Created by FIIT STU on 11/19/2021.
//

#include "scene_window.h"
#include "src/outside_objects/skybox.h"
#include "src/outside_objects/building.h"
#include "src/outside_objects/tumbleweed.h"
#include "terrain_desert.h"
#include "staticObject.h"
#include "utilities/utils.h"
#include "src/outside_objects/doors/double_doors.h"
#include "src/interior_objects/slot_machine/screen.h"
#include "src/interior_objects/slot_machine/slot_machine.h"

//void SceneWindow::createIndoorScene() {
    //auto indoorScene = std::make_shared<Scene>(*this);
   //scenes.push_back(indoorScene);

   //scene.objects.clear();

    // Create a camera
//    auto camera = std::make_unique<Camera>(60.0f, 1.0f, 0.1f, 100.0f);
//    camera->position.z = -15.0f;
//    scene.camera = move(camera);

void SceneWindow::generateTerrain(int TERRAIN_SIZE, int object_count) {
    std::vector<glm::vec3> points = Utils::generatePoints(TERRAIN_SIZE, object_count, {0,0});
    for(glm::vec3 pos : points)
    {
        std::cout << pos.x << " " << pos.y << " " << pos.z << '\n';
        auto object = std::make_unique<StaticObject>(1, pos, glm::vec3 {0,0,0}, glm::vec3 {3,3,3});
        scene.objects.push_back(move(object));
    }


}

void SceneWindow::createOutdoorScene() {
    const int TERRAIN_SIZE = 200;



    scene.objects.clear();

    generateTerrain(TERRAIN_SIZE, 200);

    // Create a camera
    auto camera = std::make_unique<Camera>(60.0f, 1.0f, 0.1f, 250.0f);
    scene.camera = move(camera);

    // Add background
    scene.objects.push_back(std::make_unique<SkyBox>(glm::vec3{TERRAIN_SIZE,TERRAIN_SIZE,TERRAIN_SIZE}));

    scene.objects.push_back(std::make_unique<terrain_desert>());
    scene.objects.push_back(std::make_unique<Building>());
    scene.objects.push_back(std::make_unique<DoubleDoors>(glm::vec3 {0,0,5.8}));
    scene.objects.push_back(std::make_unique<SlotMachine>());

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
    time = (float) glfwGetTime();
    scene.age += dt;

    // Set gray background

    glClearColor(.5f, .5f, .5f, 0);
    // Clear depth and color buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Update and render all objects
    scene.update(dt);
    scene.render();
}
