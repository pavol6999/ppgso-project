#include <memory>

#include <glm/glm.hpp>
#include <ppgso/ppgso.h>

/*!
 * Simple camera object that keeps track of viewMatrix and projectionMatrix
 * the projectionMatrix is by default constructed as perspective projection
 * the viewMatrix is generated from up, position and back vectors on update
 */
class Camera {
public:

    glm::vec3 up{0,1,0};
    glm::vec3 position{0,25,50};
    glm::vec3 back{0,0,-1};
    glm::vec3 center{0.,0.,0.};

    struct key_frame {
        const glm::vec3 position;
        const glm::vec3 center;
        glm::vec3 duration;
        float age = 0;
    };

    std::vector<key_frame> key_frames;
    size_t current_key = 0;

    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;



    /*!
     * Create new Camera that will generate viewMatrix and projectionMatrix based on its position, up and back vectors
     * @param fow - Field of view in degrees
     * @param ratio - Viewport screen ratio (usually width/height of the render window)
     * @param near - Distance to the near frustum plane
     * @param far - Distance to the far frustum plane
     */
    Camera(float fow = 45.0f, float ratio = 1.0f, float near = 0.1f, float far = 800.0f);

    /*!
     * Update Camera viewMatrix based on up, position and back vectors
     */
    void update(float dt);

    void animate(float dt);
    /*!
     * Get direction vector in world coordinates through camera projection plane
     * @param u - camera projection plane horizontal coordinate [-1,1]
     * @param v - camera projection plane vertical coordinate [-1,1]
     * @return Normalized vector from camera position to position on the camera projection plane
     */
    glm::vec3 cast(double u, double v);

};

