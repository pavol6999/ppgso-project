//
// Created by FIIT STU on 11/19/2021.
//

#ifndef PPGSO_SCENE_WINDOW_H
#define PPGSO_SCENE_WINDOW_H


//
// Created by FIIT STU on 11/19/2021.
//
#include <ppgso/ppgso.h>
#include <string>
#include "scene.h"

class SceneWindow : public ppgso::Window {
private:
    Scene scene;
    // size_t activeScene = 0; // set the active scene
    //bool animate = true;

    void createOutdoorScene();
    void generateTerrain(int TERRAIN_SIZE, int cactus_count);
public:

    /*!
     * Construct custom game window
     */
    SceneWindow(int width, int height);

    /*!
     * Window update implementation that will be called automatically from pollEvents
     */
    void onIdle();
};


#endif //PPGSO_SCENE_WINDOW_H
