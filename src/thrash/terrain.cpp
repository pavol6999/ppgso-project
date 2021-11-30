//
// Created by FIIT STU on 11/27/2021.
//


#include "terrain.h"
#include <shaders/texture_vert_glsl.h>
#include <shaders/texture_frag_glsl.h>

using namespace std;
using namespace ppgso;
using namespace glm;


Terrain::Terrain(Scene &scene, int width_size = 128, int length_size = 128) {
    ppgso::Shader shader{texture_vert_glsl, texture_frag_glsl};
    ppgso::Texture texture{ppgso::image::loadBMP("lena2.bmp")};

    const float w = 10.f, l = 10.f;
    const int patch_size = length_size;
    GLuint i = 0;
    for (int z = 0; z < length_size; z++)
        for (int x = 0; x < width_size; x++)
        {
//            float u = z / (float)(patch_size);
//            float v = x / (float)(patch_size);
//
//            vector<vec3> help;
//
//            for (unsigned int l = 0; l<4; l++)
//            {
//                help.push_back(bezierPoint(controlPoints[l], u));
//            }

            vec3 vertex = {x/(float)width_size, 0, z/(float)length_size};
            vertex.x *= w;
            vertex.z *= l;

            // center the model
            vertex.x -= w/2;
            vertex.z -= l/2;

            vertices.push_back(vertex);

            normals.emplace_back(0, 1, 0);
        }

    for (int z = 0; z < length_size; z++)
        for (int x = 0; x < width_size; x++) {

                mesh.push_back(z*patch_size + x);
                mesh.push_back((z-1)*patch_size + x);
                mesh.push_back((z-1)*patch_size + x - 1);

                mesh.push_back(z * patch_size + x);
                mesh.push_back((i-1) * patch_size + (x-1));
                mesh.push_back(z*patch_size + (x-1));

        }


        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        // Copy positions to gpu
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

        // Set vertex program inputs
        auto position_attrib = shader.getAttribLocation("Position");
        glEnableVertexAttribArray(position_attrib);
        glVertexAttribPointer(position_attrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

        // Copy texture positions to gpu
        glGenBuffers(1, &tbo);
        glBindBuffer(GL_ARRAY_BUFFER, tbo);
        glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(glm::vec2), texCoords.data(), GL_STATIC_DRAW);

        // Set vertex program inputs
        auto texCoord_attrib = shader.getAttribLocation("TexCoord");
        glEnableVertexAttribArray(texCoord_attrib);
        glVertexAttribPointer(texCoord_attrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

        // Copy indices to gpu
        glGenBuffers(1, &ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.size() * sizeof(int), mesh.data(), GL_STATIC_DRAW);




}

Terrain::~Terrain() {
    glDeleteBuffers(1, &ibo);
    glDeleteBuffers(1, &tbo);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

bool Terrain::update(Scene &scene, float dt) {
    return true;
}

void Terrain::render(Scene &scene) {

    shader.use();
    auto win_scene = dynamic_cast<Scene*>(&scene);
    shader.setUniform("LightDirection", {0, 0, 0});
    shader.setUniform("lightColor", win_scene->bgColor);

    // use camera
    shader.setUniform("ProjectionMatrix", win_scene->camera->projectionMatrix);
    shader.setUniform("ViewMatrix", translate(glm::mat4{1.0f}, {0.0f, 0.0f, 0.f}));

    // render mesh
    shader.setUniform("ModelMatrix", modelMatrix);
    shader.setUniform("Texture", texture);


    glBindVertexArray(vao);
    // TODO: Use correct rendering mode to draw the result

    glDrawElements(GL_TRIANGLES, (GLsizei) mesh.size() * 3, GL_UNSIGNED_INT , 0);
}




