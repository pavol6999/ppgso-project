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
#include "src/interior_objects/human/human.h"

void SceneWindow::generateTerrain(int TERRAIN_SIZE, int object_count) {
    std::vector<glm::vec3> points = Utils::generatePoints(TERRAIN_SIZE, object_count, {0,0});
    glm::vec3 scale;

    glm::vec3 rotation;
    for(glm::vec3 pos : points)
    {

        int random = (rand() % 5);
        if (random == 1 || random == 0) {
            scale = {3,3,3};
            rotation = {0,0,0};
            auto object = std::make_unique<StaticObject>(random, pos, rotation, scale);
            scene.objects.push_back(move(object));
        }
        else if(random == 2)
        {
            int rock_size = rand() % 3;
            scale = {0.5,0.5,0.5};
            rotation = {(rand()%628)/100,(rand()%628)/100,(rand()%628)/100};
            auto object = std::make_unique<StaticObject>(random, pos, rotation, scale);
            scene.objects.push_back(move(object));
        }
        else if (random == 3)
        {

            scale = {1,1,1};
            rotation = {0,0,0};
            auto object = std::make_unique<StaticObject>(random, pos, rotation, scale);
            scene.objects.push_back(move(object));
        }
        else if (random == 4)
        {
            auto object = std::make_unique<Tumbleweed>(pos);
            scene.objects.push_back(move(object));
        }


    }


}

void SceneWindow::createOutdoorScene() {
    const int TERRAIN_SIZE = 200;

    scene.objects.clear();

    generateTerrain(TERRAIN_SIZE, 420);

    auto camera = std::make_unique<Camera>(60.0f, 1.0f, 0.1f, 250.0f);
    auto sun = std::make_unique<Sun>(0,glm::vec3{0,100,50});
    scene.camera = move(camera);
    //scene.lightSources.push_back(std::make_unique<Sun>(0, scene.camera->position));
    scene.sun = move(sun);

    //scene.lightSources.push_back(std::make_unique<ColorBulb>(glm::vec3 {10,2,2},1));
    //scene.lightSources.push_back(std::make_unique<ColorBulb>(glm::vec3 {-2,10,-30},2));


    //scene.spotlights.push_back(std::make_unique<Spotlight>(glm::vec3 {0,20,-10},glm::vec3{0,2,0},1));
    scene.spotlights.push_back(std::make_unique<Spotlight>(glm::vec3 {-20,15,30},glm::vec3{-3,2,2},0));
    //scene.spotlights.push_back(std::make_unique<Spotlight>(glm::vec3 {20,15,30},glm::vec3{3,2,2},2));



    // Add background

    scene.objects.push_back(std::make_unique<SkyBox>(glm::vec3{TERRAIN_SIZE,TERRAIN_SIZE,TERRAIN_SIZE}));

    scene.objects.push_back(std::make_unique<terrain_desert>());
    scene.objects.push_back(std::make_unique<Building>());

    scene.objects.push_back(std::make_unique<StaticObject>(1, glm::vec3{0,0,10}, glm::vec3{0,0,0},glm::vec3 {1,1,1}));


    scene.objects.push_back(std::make_unique<SlotMachine>(glm::vec3{0.9,0,0},glm::vec3{0,0,1.6}));

    scene.objects.push_back(std::make_unique<DoubleDoors>(glm::vec3 {0,0,5.8}));

    scene.objects.push_back(std::make_unique<StaticObject>(0,glm::vec3  {0,0,15},glm::vec3 {0,0,1},glm::vec3{1,1,1}));
    scene.objects.push_back(std::make_unique<Human>(glm::vec3{0,1.65,0},glm::vec3{0,0,1.6}));
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

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Set gray background

    scene.update(dt);
    scene.render();

    // Update and render all objects

}
