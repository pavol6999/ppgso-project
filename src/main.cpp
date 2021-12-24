#include <iostream>
#include <string>
#include <map>
#include <cstdlib>
#include <src/utilities/utils.h>

#include <ppgso/ppgso.h>
#include <Windows.h>
#include "scene_window.h"

const unsigned int window_size = 1024;

int main() {

    // Initialize our window

    SceneWindow window = SceneWindow(window_size, window_size);

    while (window.pollEvents()) {}


    return EXIT_SUCCESS;
}
