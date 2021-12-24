//
// Created by FIIT STU on 11/30/2021.
//

#include <glm/detail/type_vec2.hpp>

#include <bits/stdc++.h>
#include "utils.h"
#include <iostream>
#include <cmath>
#include <ppgso.h>



// generate random uniform points inside 2D circle
std::vector<glm::vec3> Utils::generatePoints(int radius, int n, glm::vec2 center) {
    std::vector<glm::vec3> points;

    // calculate radius and subtract offset so objects do not generate at the edge of the plane
    radius -= 10;

    while((int)points.size() != n){
        // calculate angle theta
        double theta = 2 * ppgso::PI * uniform();

        // Get length from center
        double len = sqrt(uniform()) * radius;

        float x = round((center.x + len * cos(theta))/2)*2;
        float y = round((center.y + len * sin(theta))/2)*2;

        bool dont_generate = false;
        for(auto i: points){
            if ( abs(x - i.x) < 3 && abs(y - i.z) < 3) {
                dont_generate = true;
                continue;
            }
        }
        if (dont_generate)
        {
            continue;
        }
        // if the point is located near the casino
        double d = sqrt(pow((x - center.x),2) + pow((y - center.y),2));

        if ( d < 30 || (y > 30 && y < 50))
            continue;


        // the y coordinate is actually the z in our world system
        points.push_back({x,0,y});
    }
    return points;
}

double Utils::uniform() {
    return (double)rand() / RAND_MAX;
}
