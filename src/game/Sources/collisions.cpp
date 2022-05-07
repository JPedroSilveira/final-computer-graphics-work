#include "../Headers/collisions.h"

glm::vec4 convertPointToObjPosition(GameObject obj, glm::vec3 point) {
    glm::mat4 pos = matrices::Matrix_Translate(obj.position.x, obj.position.y, obj.position.z);
    glm::mat4 sca = matrices::Matrix_Scale(obj.scale.x, obj.scale.y, obj.scale.z);
    glm::mat4 rot = matrices::Matrix_Rotate_X(obj.rotation.x)*
                       matrices::Matrix_Rotate_Y(obj.rotation.y)*
                       matrices::Matrix_Rotate_Z(obj.rotation.z);

    glm::vec4 vec4Point(point.x, point.y, point.z, 1.0);

    return pos*sca*rot*vec4Point;
}

bool CollisionCubePlane(GameObject cube, GameObject plane) {
    glm::vec4 cubeMin = convertPointToObjPosition(cube, cube.model.bbox_min);
    glm::vec4 cubeMax = convertPointToObjPosition(cube, cube.model.bbox_max);

    glm::vec4 cubeCenter = matrices::component_wise_division((cubeMax + cubeMin), 2.0);
    glm::vec4 extents = cubeMax - cubeCenter;

    auto model = plane.model;
    auto planeNormal = matrices::normalize(
        convertPointToObjPosition(
            plane, 
            glm::vec3(
                model.attrib.normals[0], 
                model.attrib.normals[1], 
                model.attrib.normals[2]
            )
        )
    );

    float r = extents.x * abs(planeNormal.x) + 
        extents.y * abs(planeNormal.y) + 
        extents.z * abs(planeNormal.z);

    planeNormal[3] = 0.0f;
    cubeCenter[3] = 0.0f;

    float d = 9.8f;
    if (planeNormal.z == 0.0f) {
        if (planeNormal.x > 0.0f) {
            d = 9.8f;
        } else {
            d = 10.8f;
        }
    }

    float s = matrices::dotproduct(planeNormal, cubeCenter) - d;

    return abs(s) <= r;
}

// Calcula se a bouding box do primeiro parâmetro tem colisão com a 
// bouding box do segundo
bool CollisionCubeCube(GameObject a, GameObject b) {
    glm::vec4 aMin = convertPointToObjPosition(a, a.model.bbox_min);
    glm::vec4 aMax = convertPointToObjPosition(a, a.model.bbox_max);
    glm::vec4 bMin = convertPointToObjPosition(b, b.model.bbox_min);
    glm::vec4 bMax = convertPointToObjPosition(b, b.model.bbox_max);

    bool xCondition = (aMin.x <= bMax.x) && (aMax.x >= bMin.x);
    bool yCondition = (aMin.y <= bMax.y) && (aMax.y >= bMin.y);
    bool zCondition = (aMin.z <= bMax.z) && (aMax.z >= bMin.z);
    return xCondition && yCondition && zCondition;
}

// Calcula se a bouding box do primeiro parâmetro tem colisão com a 
// esféra do segundo parâmetro. Obs.: a caixa da esféra é calculada com base
// na bouding box considerando o raio como a métada da maior dimensão, 
// dada uma esfera real todas as dimensões terão o mesmo tamanho
bool CollisionCubeSphere(GameObject cube, GameObject sphere) {
    glm::vec4 cubeMin = convertPointToObjPosition(cube, cube.model.bbox_min);
    glm::vec4 cubeMax = convertPointToObjPosition(cube, cube.model.bbox_max);
    glm::vec4 sphereMin = convertPointToObjPosition(sphere, sphere.model.bbox_min);
    glm::vec4 sphereMax = convertPointToObjPosition(sphere, sphere.model.bbox_max);

    float d1 = abs(sphereMax.x - sphereMin.x);
    float d2 = abs(sphereMax.y - sphereMin.y);
    float d3 = abs(sphereMax.z - sphereMin.z);
    glm::vec4 sphereCenter = matrices::component_wise_division((sphereMin + sphereMax), 2.0);

    float radius = std::max(std::max(d1, d2), d3) / 2;

    float closestX = std::max(cubeMin.x, std::min(sphereCenter.x, cubeMax.x));
    float closestY = std::max(cubeMin.y, std::min(sphereCenter.y, cubeMax.x));
    float closestZ = std::max(cubeMin.z, std::min(sphereCenter.z, cubeMax.z));

    float distanceX = closestX - sphereCenter.x;
    float distanceY = closestY - sphereCenter.y;
    float distanceZ = closestZ - sphereCenter.z;

    float distance = sqrt(pow(distanceX, 2) + pow(distanceY, 2) + pow(distanceZ, 2));

    return distance < radius;
}