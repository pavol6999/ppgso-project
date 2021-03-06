#include "double_doors.h"
#include "src/scene.h"


DoubleDoors::DoubleDoors(glm::vec3 pos) {
    left = std::make_unique<Doors>(pos);
    left->key_frames.push_back({{3,3,3}, pos});
    left->key_frames.push_back({{3,3,3}, left->position + glm::vec3 {1.5,0,0}});
    left->key_frames.push_back({{3,3,3}, pos});

    right = std::make_unique<Doors>(pos + glm::vec3 {-1.5,0,0});
    right->key_frames.push_back({{3,3,3}, pos + glm::vec3 {-1.5,0,0}});
    right->key_frames.push_back({{3,3,3}, right->position + glm::vec3 {-1.5,0,0}});
    right->key_frames.push_back({{3,3,3}, pos + glm::vec3 {-1.5,0,0}, glm::vec3 {0,0,0}});
}

bool DoubleDoors::update(Scene &scene, float dt) {
    left->update(scene,dt);
    right->update(scene,dt);
    return true;
}

void DoubleDoors::render(Scene &scene) {
    left->render(scene);
    right->render(scene);
}

