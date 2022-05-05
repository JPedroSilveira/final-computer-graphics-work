#include "../Headers/collisions.h"

glm::vec4 convertBoudingBox(GameObject obj, glm::vec3 point) {
    glm::mat4 pos = matrices::Matrix_Translate(obj.position.x, obj.position.y, obj.position.z);
    glm::mat4 sca = matrices::Matrix_Scale(obj.scale.x, obj.scale.y, obj.scale.z);

    printf("Point X: %f \n", point.x);
           
    glm::vec4 vec4Point(point.x, point.y, point.z, 1.0);

    return pos*sca*vec4Point;
}

bool CollisionCubePlane(GameObject cubeObject, GameObject planObject) {
    // TODO: calculate collision
    return false;
}

bool CollisionCubeCube(GameObject a, GameObject b) {
    glm::vec4 aMin = convertBoudingBox(a, a.model.bbox_min);
    glm::vec4 aMax = convertBoudingBox(a, a.model.bbox_max);
    glm::vec4 bMin = convertBoudingBox(b, b.model.bbox_min);
    glm::vec4 bMax = convertBoudingBox(b, b.model.bbox_max);

    bool xCondition = (aMin.x <= bMax.x) && (aMax.x >= bMin.x);
    bool yCondition = (aMin.y <= bMax.y) && (aMax.y >= bMin.y);
    bool zCondition = (aMin.z <= bMax.z) && (aMax.z >= bMin.z);
    return xCondition && yCondition && zCondition;
}
bool CollisionCubeSphere(GameObject cubeObject, GameObject sphereObject) {
    // TODO: calculate collision
    return false;
}