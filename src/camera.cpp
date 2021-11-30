#include <glm/glm.hpp>

#include "camera.h"

void Camera::animate(float dt) {
    if (current_key == key_frames.size() - 1) {
        position = key_frames[current_key].position;
        center = key_frames[current_key].center;
        return;
    }

    position += (dt*(key_frames[current_key + 1].position - key_frames[current_key].position))/key_frames[current_key].duration;
    center += (dt*(key_frames[current_key + 1].center - key_frames[current_key].center))/key_frames[current_key].duration;

    key_frames[current_key].age += dt;

    if (key_frames[current_key].age >= key_frames[current_key].duration.x) {
        current_key++;
    }
}


Camera::Camera(float fow, float ratio, float near, float far) {
    float fowInRad = (ppgso::PI/180.0f) * fow;

    key_frames.push_back({glm::vec3{0,2,50},glm::vec3{0,0,0},glm::vec3{5,5,5}});
    key_frames.push_back({glm::vec3{0,15,25},glm::vec3{0,0,0}, glm::vec3{5,5,5}});
    key_frames.push_back({glm::vec3{0,2,10},glm::vec3{0,2,0}, glm::vec3{5,5,5}});

    projectionMatrix = glm::perspective(fowInRad, ratio, near, far);
}


void Camera::update(float dt) {
    animate(dt);
    viewMatrix = lookAt(position, center, up);

}

glm::vec3 Camera::cast(double u, double v) {
    // Create point in Screen coordinates
    glm::vec4 screenPosition{u,v,0.0f,1.0f};

    // Use inverse matrices to get the point in world coordinates
    auto invProjection = glm::inverse(projectionMatrix);
    auto invView = glm::inverse(viewMatrix);

    // Compute position on the camera plane
    auto planePosition = invView * invProjection * screenPosition;
    planePosition /= planePosition.w;

    // Create direction vector
    auto direction = glm::normalize(planePosition - glm::vec4{position,1.0f});
    return glm::vec3{direction};
}
