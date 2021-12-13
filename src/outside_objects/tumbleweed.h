//
// Created by Administrator on 29/11/2021.
//

#ifndef PPGSO_TUMBLEWEED_H
#define PPGSO_TUMBLEWEED_H

class Tumbleweed final : public Object {
private:
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture;


public:

    Tumbleweed(glm::vec3 pos);

    bool update(Scene &scene, float dt) override;

    void render(Scene &scene) override;
};

#endif //PPGSO_TUMBLEWEED_H
