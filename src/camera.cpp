#include <glm/glm.hpp>

#include "camera.h"

constexpr glm::vec3 step = {0,0,0};

glm::vec3 calc_step(glm::vec3 start, glm::vec3 end, uint32_t steps) {
    glm::vec3 diff = end - start;
    diff /= steps;
    return diff;
}

void Camera::animate() {
    if (current_key == key_frames.size() - 1) {
        position = key_frames[current_key].position;
        center = key_frames[current_key].center;
        return;
    }
    if (key_frames[current_key].step_pos == step) {
        key_frames[current_key].step_pos = calc_step(key_frames[current_key].position, key_frames[current_key + 1].position,
                                                 key_frames[current_key].duration);
    }
    if (key_frames[current_key].step_cent == step) {
        key_frames[current_key].step_cent = calc_step(key_frames[current_key].center, key_frames[current_key + 1].center,
                                                     key_frames[current_key].duration);
    }
    glm::vec3 curr_step = {key_frames[current_key].curr_step, key_frames[current_key].curr_step,
                           key_frames[current_key].curr_step};


    position = key_frames[current_key].position + key_frames[current_key].step_pos * curr_step;
    center = key_frames[current_key].center + key_frames[current_key].step_cent * curr_step;
    key_frames[current_key].curr_step++;

    if (key_frames[current_key].curr_step == key_frames[current_key].duration) {
        current_key++;
    }
}


Camera::Camera(float fow, float ratio, float near, float far) {
    float fowInRad = (ppgso::PI/180.0f) * fow;

    key_frames.push_back({glm::vec3{0,2,50},
                          glm::vec3{0,0,0},
                          200});
    key_frames.push_back({glm::vec3{0,15,25},glm::vec3{0,0,0}, 200});


    projectionMatrix = glm::perspective(fowInRad, ratio, near, far);
}

void Camera::update(float dt) {
    animate();
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
