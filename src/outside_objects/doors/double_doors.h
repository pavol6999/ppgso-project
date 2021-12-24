#ifndef PPGSO_DOUBLE_DOORS_H
#define PPGSO_DOUBLE_DOORS_H

#include <glm/glm.hpp>
#include <glm/vec3.hpp>

#include "doors.h"
#include "src/object.h"

class Scene;


class DoubleDoors : public Object{
private:
    std::unique_ptr<Doors> left;
    std::unique_ptr<Doors> right;

public:
    explicit DoubleDoors(glm::vec3 pos);

    bool update(Scene &scene, float dt);

    void render(Scene &scene);
};

#endif //PPGSO_DOUBLE_DOORS_H
