//
// Created by FIIT STU on 11/30/2021.
//

#ifndef PPGSO_UTILS_H
#define PPGSO_UTILS_H

#include <vector>
#include <glm/vec3.hpp>




class Utils {
    static double uniform();

public:
    static std::vector<glm::vec3> generatePoints(int radius, int n, glm::vec2 center);
};


#endif //PPGSO_UTILS_H
