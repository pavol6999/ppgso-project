
#ifndef PPGSO_SCENE_WINDOW_H
#define PPGSO_SCENE_WINDOW_H

#include <ppgso/ppgso.h>
#include <string>
#include "scene.h"

class SceneWindow : public ppgso::Window {
private:
    unsigned int depthMap;
    const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
    unsigned int depthMapFBO;
    Scene scene;

    void createScene();
    void generateInterior();
    void drop_confetti();
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
