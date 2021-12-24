#ifndef PPGSO_VIRTUALOBJECT_H
#define PPGSO_VIRTUALOBJECT_H
#include <ppgso/ppgso.h>
#include <vector>
#include "src/object.h"

using namespace std;
using namespace ppgso;
using namespace glm;

class VirtualObject : public Object {

protected:

    vector<vec3> vertices;
    vector<vec2> texCoords;
    vector<vec3> normals;

    struct Face {
        GLuint v0, v1, v2;
    };

    vector<Face> mesh;

    GLuint vao = 0;
    GLuint vbo = 0;
    GLuint tbo = 0;
    GLuint nbo = 0;
    GLuint ibo = 0;
    mat4 modelMatrix{1.0f};


public:
    vec3 position{0,0,0};
    vec3 rotation{0,0,0};
    vec3 scale{1,1,1};


    VirtualObject() {
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &tbo);
        glGenBuffers(1, &ibo);
        glGenBuffers(1, &nbo);
    }

    ~VirtualObject() override {
        glDeleteBuffers(1, &ibo);
        glDeleteBuffers(1, &tbo);
        glDeleteBuffers(1, &vbo);
        glDeleteVertexArrays(1, &vao);
    }

    void setVertexBuffer(std::unique_ptr<ppgso::Shader>& shader) {
        // Copy positions to gpu
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), vertices.data(), GL_STATIC_DRAW);

        // Set vertex program inputs
        auto position_attrib = shader->getAttribLocation("Position");
        glEnableVertexAttribArray(position_attrib);
        glVertexAttribPointer(position_attrib, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    }

    void setTextureBuffer(std::unique_ptr<ppgso::Shader>& shader) {
        // Copy texture positions to gpu
        glBindBuffer(GL_ARRAY_BUFFER, tbo);
        glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(glm::vec2), texCoords.data(), GL_STATIC_DRAW);

        // Set vertex program inputs
        auto texCoord_attrib = shader->getAttribLocation("TexCoord");
        glEnableVertexAttribArray(texCoord_attrib);
        glVertexAttribPointer(texCoord_attrib, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    }

    void setNormalBuffer(std::unique_ptr<ppgso::Shader>& shader) {
        glBindBuffer(GL_ARRAY_BUFFER, nbo);
        glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), normals.data(),
                     GL_STATIC_DRAW);

        auto normalCoord_attrib = shader->getAttribLocation("Normal");
        glEnableVertexAttribArray(normalCoord_attrib);
        glVertexAttribPointer(normalCoord_attrib, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    }

    void setIndexBuffer() {
        // Copy indices to gpu
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.size() * sizeof(int), mesh.data(), GL_STATIC_DRAW);
    }
};


#endif //PPGSO_VIRTUALOBJECT_H
