//
// Created by FIIT STU on 11/19/2021.
//

#include <iostream>
#include <string>
#include <map>

#include <src/utilities/utils.h>

#include <ppgso/ppgso.h>
#include "scene_window.h"

const unsigned int SIZE = 1024;

int main() {

    // Initialize our window
    auto penis = ppgso::image::loadBMP("heightmap.bmp");
    SceneWindow window = SceneWindow(SIZE, SIZE);
    while (window.pollEvents()) {}


    return EXIT_SUCCESS;
}
