//
// Created by FIIT STU on 11/30/2021.
//

#include <glm/detail/type_vec2.hpp>

#include <bits/stdc++.h>
#include "utils.h"
#include <ppgso.h>


// generate random uniform points inside 2D circle
std::vector<glm::vec3> Utils::generatePoints(int radius, int n, glm::vec2 center) {
    std::vector<glm::vec3> points;

    // calculate radius and subtract offset so objects do not generate at the edge of the plane


    for (int i = 0; i < n; i++){
        // calculate angle theta
        double theta = 2 * ppgso::PI * uniform();

        // Get length from center
        double len = sqrt(uniform()) * radius;

        float x = center.x + len * cos(theta);
        float y = center.y + len * sin(theta);

        // if the point is located inside the casino
        if( -3 < x && x < 3)
        {
            x += x + 16;
        }
        if( -3 < y && y < 3)
        {
            y += y - 16;
        }


        // the y coordinate is actually the z in our world system
        points.push_back({x,0,y});
    }
    return points;
}

double Utils::uniform() {
    return (double)rand() / RAND_MAX;
}
