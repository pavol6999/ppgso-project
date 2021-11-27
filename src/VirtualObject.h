//
// Created by FIIT STU on 11/27/2021.
//

#ifndef PPGSO_VIRTUALOBJECT_H
#define PPGSO_VIRTUALOBJECT_H
#include <ppgso/ppgso.h>
#include <vector>
#include <shaders/texture_vert_glsl.h>
#include <shaders/texture_frag_glsl.h>
#include "object.h"

using namespace std;
using namespace ppgso;
using namespace glm;

class VirtualObject : Object {

private:
    vector<vec3> vertices;
    vector<vec2> texCoords;

    struct Face {
        GLuint v0, v1, v2;
    };

    vector<Face> mesh;

    GLuint vao = 0;
    GLuint vbo = 0;
    GLuint tbo = 0;
//    GLuint nbo = 0;
    GLuint ibo = 0;
    mat4 modelMatrix{1.0f};
    Shader program{texture_vert_glsl, texture_frag_glsl};

public:
    vec3 position{0,0,0};
    vec3 rotation{0,0,0};
    vec3 scale{1,1,1};


    VirtualObject() {
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), vertices.data(), GL_STATIC_DRAW);


        auto position_attrib = program.getAttribLocation("Position");
        glEnableVertexAttribArray(position_attrib);
        glVertexAttribPointer(position_attrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

        glGenBuffers(1, &tbo);
        glBindBuffer(GL_ARRAY_BUFFER, tbo);
        glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(vec2), texCoords.data(), GL_STATIC_DRAW);

        // Set vertex program inputs
        auto texCoord_attrib = program.getAttribLocation("TexCoord");
        glEnableVertexAttribArray(texCoord_attrib);
        glVertexAttribPointer(texCoord_attrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

        glGenBuffers(1, &ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.size() * sizeof(Face), mesh.data(), GL_STATIC_DRAW);

//        glGenBuffers(1, &nbo);
    }

    ~VirtualObject() override {
        glDeleteBuffers(1, &ibo);
        glDeleteBuffers(1, &tbo);
        glDeleteBuffers(1, &vbo);
        glDeleteVertexArrays(1, &vao);
    }

};


#endif //PPGSO_VIRTUALOBJECT_H
