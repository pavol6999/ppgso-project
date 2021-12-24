#ifndef PPGSO_TERRAIN_H
#define PPGSO_TERRAIN_H

#include <ppgso/ppgso.h>
#include <src/utilities/VirtualObject.h>
#include <src/scene.h>
#include <dependencies/include/glm/vec3.hpp>
#include <shader.h>

class Terrain : public Object {

private:
    // 3D vectors define points/vertices of the shape
    std::vector<glm::vec3> vertices;

    // Texture coordinates
    std::vector<glm::vec2> texCoords;

    struct face {
        GLuint v0, v1, v2;
    };
    // Define our mesh as collection of faces
    std::vector<GLuint> mesh;



    std::vector<glm::vec3> normals;

    // These will hold the data and object buffers
    GLuint vao = 0, vbo = 0, tbo = 0, ibo = 0;
    glm::mat4 modelMatrix{1.0f};

    Shader shader;
    Texture texture;


    int width = 128;
    int length = 128;
    float time = 0;






public:

    glm::vec3 position{1,0,0};
    glm::vec3 rotation{0,0,0};
    glm::vec3 scale{1,1,1};

    explicit Terrain(Scene &scene, int width, int length);
    ~Terrain();
    bool update(Scene &scene, float dt) override;

    void render(Scene &scene) override;
};


#endif //PPGSO_TERRAIN_H
