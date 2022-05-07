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

// Calcula se a bouding box do primeiro parâmetro tem colisão com algum 
// ponto do segundo parâmetro
bool CollisionCubePlane(GameObject cube, GameObject plane) {
    glm::vec4 cubeMin = convertPointToObjPosition(cube, cube.model.bbox_min);
    glm::vec4 cubeMax = convertPointToObjPosition(cube, cube.model.bbox_max);
 
    // printf("\n Plane Min X: %f", planeMin.x);
    // printf("\n Plane Min Y: %f", planeMin.y);
    // printf("\n Plane Max X: %f", planeMax.x);
    // printf("\n Plane Max Y: %f", planeMax.y);

    // printf("\n Plane Min Z %f", planeMin.z);
    // printf("\n Plane Max Z: %f", planeMax.z);

    auto model = plane.model;
    
    for (size_t shape = 0; shape < model.shapes.size(); ++shape)
    {
        size_t num_triangles = model.shapes[shape].mesh.num_face_vertices.size();

        for (size_t triangle = 0; triangle < num_triangles; ++triangle)
        {
            assert(model.shapes[shape].mesh.num_face_vertices[triangle] == 3);
            
            for (size_t vertex = 0; vertex < 3; ++vertex)
            {
                tinyobj::index_t idx = model.shapes[shape].mesh.indices[3*triangle + vertex];

                const float vx = model.attrib.vertices[3*idx.vertex_index + 0];
                const float vy = model.attrib.vertices[3*idx.vertex_index + 1];
                const float vz = model.attrib.vertices[3*idx.vertex_index + 2];
    
                // TODO test
            }
        }

    }

    return false;
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