#include "scene.h"

void Scene::update(float time) {
    camera->update(time);


    if(!sun->update(*this,time))
    {
        auto ptr = sun.release();
        ptr = nullptr;
        delete ptr;

    }

    auto i = std::begin(objects);
    while (i != std::end(objects)) {
        // Update and remove from list if needed
        auto obj = i->get();
        if (!obj->update(*this, time))
            i = objects.erase(i); // NOTE: no need to call destructors as we store shared pointers in the scene
        else
            ++i;
    }


    auto j = std::begin(lightSources);
    while (j != std::end(lightSources)) {
        // Update and remove from list if needed
        auto obj = j->get();
        if (!obj->update(*this, time))
            j = lightSources.erase(j); // NOTE: no need to call destructors as we store shared pointers in the scene
        else
            ++j;
    }

    auto l = std::begin(spotlights);
    while (l != std::end(spotlights)) {
        // Update and remove from list if needed
        auto obj = l->get();
        if (!obj->update(*this, time))
            l = spotlights.erase(l); // NOTE: no need to call destructors as we store shared pointers in the scene
        else
            ++l;
    }
}



void Scene::render() {
    for (auto &obj : objects) {
        obj->render(*this);
    }
}
