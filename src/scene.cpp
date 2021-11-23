#include "scene.h"



void Scene::update(float time) {
    camera->update();

    auto i = std::begin(objects);
    while (i != std::end(objects)) {
        // Update and remove from list if needed
        auto obj = i->get();
        if (!obj->update(*this, time))
            i = objects.erase(i); // NOTE: no need to call destructors as we store shared pointers in the scene
        else
            ++i;
    }
}

void Scene::render() {
    for (auto &obj : objects) {
        obj->render(*this);
    }

}
