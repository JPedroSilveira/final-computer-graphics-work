#include "../Headers/collisions.h"

glm::vec4 convertBoudingBox(GameObject obj, glm::vec3 point) {
    // glm::vec4 p_world = model*p_model;
    glm::mat4 pos = matrices::Matrix_Translate(obj.position.x, obj.position.y, obj.position.z);
    glm::mat4 sca = matrices::Matrix_Scale(obj.scale.x, obj.scale.y, obj.scale.z);
    glm::mat4 rot = matrices::Matrix_Rotate_X(obj.rotation.x)*
                matrices::Matrix_Rotate_Y(obj.rotation.y)*
                matrices::Matrix_Rotate_Z(obj.rotation.z);

    printf("Point X: %f \n", point.x);
           
    glm::vec4 vec4Point(point.x, point.y, point.z, 1.0);

    return pos*sca*rot*vec4Point;
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

    printf("Galinha X[Min]: %f \n", aMin.x);
    printf("Galinha Y[Min]: %f \n", aMin.y);
    printf("Galinha Z[Min]: %f \n", aMin.z);
    printf("Galinha X[Max]: %f \n", aMax.x);
    printf("Galinha Y[Max]: %f \n", aMax.y);
    printf("Galinha Z[Max]: %f \n", aMax.z);

    printf("Coelho X[Min]: %f \n", bMin.x);
    printf("Coelho Y[Min]: %f \n", bMin.y);
    printf("Coelho Z[Min]: %f \n", bMin.z);
    printf("Coelho X[Max]: %f \n", bMax.x);
    printf("Coelho Y[Max]: %f \n", bMax.y);
    printf("Coelho Z[Max]: %f \n", bMax.z);

    bool xCondition = aMin.x <= bMax.x && aMax.x >= bMin.x;
    bool yCondition = aMin.y <= bMax.y && aMax.y >= bMin.y;
    bool zCondition = aMin.z <= bMax.z && aMax.z >= bMin.z;
    return xCondition && yCondition && zCondition;
}
bool CollisionCubeSphere(GameObject cubeObject, GameObject sphereObject) {
    // TODO: calculate collision
    return false;
}