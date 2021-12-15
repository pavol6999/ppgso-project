#include <glm/glm.hpp>

#include "camera.h"

void Camera::animate(float dt) {
    if (current_key == key_frames.size() - 1) {
        return;
    }


    position += (dt*(key_frames[current_key + 1].position - key_frames[current_key].position))/key_frames[current_key].duration;
    center += (dt*(key_frames[current_key + 1].center - key_frames[current_key].center))/key_frames[current_key].duration;

    key_frames[current_key].age += dt;

    if (key_frames[current_key].age >= key_frames[current_key].duration.x) {
        key_frames[current_key + 1].position = position;
        key_frames[current_key + 1].center = center;
        current_key++;
        return;
    }
}


Camera::Camera(float fow, float ratio, float near, float far) {
    float fowInRad = (ppgso::PI/180.0f) * fow;

    key_frames.push_back({glm::vec3{0,25,50},glm::vec3{0,2,0},glm::vec3{2,2,2}});

    key_frames.push_back({glm::vec3{0,50,50},glm::vec3{0,2,0},glm::vec3{2,2,2}});
    key_frames.push_back({glm::vec3{0,50,60},glm::vec3{0,2,0},glm::vec3{5,5,5}});
    key_frames.push_back({glm::vec3{42,50,42},glm::vec3{-10,2,12},glm::vec3{4,4,4}});
    key_frames.push_back({glm::vec3{60,50,0},glm::vec3{-20,2,30},glm::vec3{5,5,5}});
    key_frames.push_back({glm::vec3{42,50,-42},glm::vec3{13,2,5},glm::vec3{4,4,4}});
    key_frames.push_back({glm::vec3{0,50,-60},glm::vec3{2,2,2},glm::vec3{5,5,5}});
    key_frames.push_back({glm::vec3{-42,50,-42},glm::vec3{30,2,20},glm::vec3{4,4,4}});
    key_frames.push_back({glm::vec3{-60,50,0},glm::vec3{0,2,0},glm::vec3{5,5,5}});
    key_frames.push_back({glm::vec3{-42,50,42},glm::vec3{0,2,0},glm::vec3{4,4,4}});
    key_frames.push_back({glm::vec3{0,30,50},glm::vec3{0,2,0}, glm::vec3{2,2,2}});
    key_frames.push_back({glm::vec3{0,30,50},glm::vec3{0,2,0}, glm::vec3{1,1,1}});
    key_frames.push_back({glm::vec3{0,30,50},glm::vec3{0,10,-30}, glm::vec3{1,1,1}}); //44 zaciatok skybox rotation
    key_frames.push_back({glm::vec3{0,30,50},glm::vec3{0,10,-30}, glm::vec3{8,8,8}}); // 52
    key_frames.push_back({glm::vec3{0,30,50},glm::vec3{0,100,0},glm::vec3{4,4,4}}); // 56
    key_frames.push_back({glm::vec3{0,30,50},glm::vec3{0,100,0},glm::vec3{3,3,3}}); // 59
    key_frames.push_back({glm::vec3{0,30,50},glm::vec3{0,2,0},glm::vec3{2,2,2}}); // 61
    key_frames.push_back({glm::vec3{0,30,50},glm::vec3{0,2,0},glm::vec3{4,4,4}}); // 65
    key_frames.push_back({glm::vec3{0,10,50},glm::vec3{-10,2,10}, glm::vec3{1,1,1}}); // 66
    key_frames.push_back({glm::vec3{0,10,50},glm::vec3{-10,2,10}, glm::vec3{2,2,2}}); // 68
    key_frames.push_back({glm::vec3{0,10,50},glm::vec3{10,2,-10}, glm::vec3{1,1,1}}); // 69 nice
    key_frames.push_back({glm::vec3{0,10,50},glm::vec3{10,2,-10}, glm::vec3{2,2,2}}); // 71
    key_frames.push_back({glm::vec3{0,10,50},glm::vec3{0,2,0},glm::vec3{2,2,2}}); // 73

    key_frames.push_back({glm::vec3{0,2,50},glm::vec3{0,2,0},glm::vec3{6,6,6}}); // 79

    key_frames.push_back({glm::vec3{0,2,8},glm::vec3{0,2,0}, glm::vec3{3,3,3}}); // 82
    key_frames.push_back({glm::vec3{0,2,8},glm::vec3{0,2,0}, glm::vec3{3,3,3}}); // 85
    key_frames.push_back({glm::vec3{0,2,5},glm::vec3{0,2,0}, glm::vec3{3,3,3}});
    key_frames.push_back({glm::vec3{0,0.1,0},glm::vec3{0,2,-5}, glm::vec3{3,3,3}});
    key_frames.push_back({glm::vec3{0,0.5,-2},glm::vec3{-2,2,1}, glm::vec3{5,5,5}});
    key_frames.push_back({glm::vec3{-8,2,-2},glm::vec3{-8,2,5}, glm::vec3{3,3,3}});
    key_frames.push_back({glm::vec3{-8,3,3},glm::vec3{-8,2,5}, glm::vec3{4,4,4}});


    position = key_frames[0].position;
    center = key_frames[0].center;
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
