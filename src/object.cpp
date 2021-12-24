#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/transform.hpp>

#include "object.h"
#include "scene.h"


void Object::generateModelMatrix() {
  modelMatrix =
          glm::translate(glm::mat4(1.0f), position)
          * glm::orientate4(rotation)
          * glm::scale(glm::mat4(1.0f), scale);
}

bool Object::check_collision(glm::vec3 pos, Scene &scene){
    // skontroluj pre každý objekt
    for (const auto& obj: scene.objects) {
        // objekt nemôže mať kolíziu sám so sebou
        if (obj.get() == this) continue;
        if (obj->can_collide) {
            // funkcia na kontrolu kolízie konkrétnej osi
            auto collision = [](float one_s, float one_l, float two_s, float two_l) {
                return ((two_s <= one_s && one_s <= two_l) || (two_s <= one_l && one_l <= two_l)) ||
                        ((one_s <= two_s && two_s <= one_l) || (one_s <= two_l && two_l <= one_l));
            };

            auto collisionX = collision(pos.x + this->bounding_box[0].x, pos.x + this->bounding_box[1].x,
                                        (obj->position.x + obj->bounding_box[0].x),
                                        (obj->position.x + obj->bounding_box[1].x));

            auto collisionY = collision(pos.y + this->bounding_box[0].y, pos.y + this->bounding_box[1].y,
                                        obj->position.y + obj->bounding_box[0].y,
                                        obj->position.y + obj->bounding_box[1].y);
            auto collisionZ = collision(pos.z + this->bounding_box[0].z, pos.z + this->bounding_box[1].z,
                                        obj->position.z + obj->bounding_box[0].z,
                                        obj->position.z + obj->bounding_box[1].z);
            //pokiaľ je na všetkých osach priesečník, objekt do niečoho narazil
            if (collisionX && collisionY && collisionZ) {
                return true;
            }
        }
    }
    return false;
}
