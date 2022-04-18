#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/vec3.hpp>

struct Material {
    glm::vec3 Kd;
    glm::vec3 Ks;
    glm::vec3 Ka;
    float q;
};

const Material base_material {
    glm::vec3(0.3,0.3,0.3),
    glm::vec3(0.3,0.3,0.3),
    glm::vec3(0.3,0.3,0.3),
    32
};

#endif