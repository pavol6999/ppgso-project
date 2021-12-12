//
// Created by FIIT STU on 11/19/2021.
//

#include <src/Lighting/colorBulb.h>
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
#include "src/interior_objects/roulette/roulette_table.h"

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
    glm::vec3 scale;
    glm::vec3 rotation;
    for(glm::vec3 pos : points)
    {

        int random = (rand() % 4);
        if (random == 1 || random == 0) {
            scale = {3,3,3};
            rotation = {0,0,0};
        }
        else if(random == 2)
        {
            int rock_size = rand() % 3;
           scale = {0.5,0.5,0.5};


        }
        else if (random == 3)
        {

            scale = {1,1,1};
        }

        auto object = std::make_unique<StaticObject>(random, pos, rotation, scale);
        scene.objects.push_back(move(object));
    }


}

void SceneWindow::createOutdoorScene() {
    const int TERRAIN_SIZE = 200;



    scene.objects.clear();

    generateTerrain(TERRAIN_SIZE, 300);

    // Create a camera

    auto camera = std::make_unique<Camera>(60.0f, 1.0f, 0.1f, 250.0f);
    auto sun = std::make_unique<Sun>(0,glm::vec3{0,100,50});
    scene.camera = move(camera);
    //scene.lightSources.push_back(std::make_unique<Sun>(0, scene.camera->position));
    scene.sun = move(sun);

    scene.lightSources.push_back(std::make_unique<ColorBulb>(glm::vec3 {10,2,2},1));
    scene.lightSources.push_back(std::make_unique<ColorBulb>(glm::vec3 {-10,2,2},2));




    // Add background
    scene.objects.push_back(std::make_unique<SkyBox>(glm::vec3{TERRAIN_SIZE,TERRAIN_SIZE,TERRAIN_SIZE}));

    scene.objects.push_back(std::make_unique<terrain_desert>());
    scene.objects.push_back(std::make_unique<Building>());

    scene.objects.push_back(std::make_unique<SlotMachine>());
    scene.objects.push_back(std::make_unique<RouletteTable>(glm::vec3{0,0,2},glm::vec3{0,0,0}));
    scene.objects.push_back(std::make_unique<DoubleDoors>(glm::vec3 {0,0,5.8}));
    //scene.objects.push_back(std::make_unique<StaticObject>(0,glm::vec3  {10,10,5},glm::vec3 {0,0,1},glm::vec3{1,1,1}));



    for (int i = 0; i < 10; i++)
        scene.objects.push_back(std::make_unique<Tumbleweed>());


}


SceneWindow::SceneWindow(const int width, const int height) : Window{"uz sme si to vsimli, pardon", width, height}
{
    // Initialize OpenGL state
    // Enable Z-buffer
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);




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
