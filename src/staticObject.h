//
// Created by FIIT STU on 11/30/2021.
//

#ifndef PPGSO_STATICOBJECT_H
#define PPGSO_STATICOBJECT_H


#include "scene.h"
#include "object.h"
#include "ppgso.h"

class StaticObject : public Object {

private:
    int obj_id;
    const static int num_obj = 2;

    static std::unique_ptr<ppgso::Mesh> mesh[num_obj];
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture[num_obj];
    static char *texNames[num_obj];

    static char *meshNames[num_obj];


public:
    StaticObject(int id, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

    bool update(Scene &scene, float dt) override;

    void render(Scene &scene) override;
};



#endif //PPGSO_STATICOBJECT_H
