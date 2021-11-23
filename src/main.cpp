//
// Created by FIIT STU on 11/19/2021.
//

#include <iostream>
#include <string>
#include <map>

#include <ppgso/ppgso.h>
#include "scene_window.h"

const unsigned int SIZE = 1024;

int main() {

    // Initialize our window
    SceneWindow window = SceneWindow(SIZE, SIZE);
    while (window.pollEvents()) {}


    return EXIT_SUCCESS;
}
