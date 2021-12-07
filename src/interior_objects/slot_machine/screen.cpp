//
// Created by Administrator on 06/12/2021.
//
#include "screen.h"
#include "src/scene.h"


#include <shaders/texture_vert_glsl.h>
#include <shaders/texture_frag_glsl.h>

Screen::Screen(glm::vec3 pos, glm::vec3 rot, glm::vec3 sc) {
    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(texture_vert_glsl, texture_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("screentex.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("screen.obj");
    textureOffset = {0,0};
    position = pos;
    rotation = rot;
    scale = sc;
}

bool Screen::update(Scene &scene, float dt) {
    // Offset for UV mapping, creates illusion of scrolling
    textureOffset.y -= dt/5;
    generateModelMatrix();
    return true;
}

void Screen::render(Scene &scene) {
    // Disable writing to the depth buffer so we render a "background"
    glDepthMask(GL_FALSE);

    // NOTE: this object does not use camera, just renders the entire quad as is
    shader->use();

    // Pass UV mapping offset to the shader
    shader->setUniform("TextureOffset", textureOffset);

    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    // render mesh
    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);
    shader->setUniform("CameraPosition", scene.camera->position);

    mesh->render();

    glDepthMask(GL_TRUE);
}

// shared resources
std::unique_ptr<ppgso::Mesh> Screen::mesh;
std::unique_ptr<ppgso::Shader> Screen::shader;
std::unique_ptr<ppgso::Texture> Screen::texture;