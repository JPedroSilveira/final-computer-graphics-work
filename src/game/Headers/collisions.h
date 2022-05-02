#ifndef COLLISIONS_H
#define COLLISIONS_H

#include "object.h"

bool CollisionCubePlane(GameObject cubeObject, GameObject planObject);
bool CollisionCubeCube(GameObject cubeObjectOne, GameObject cubeObjectTwo);
bool CollisionCubeSphere(GameObject cubeObject, GameObject sphereObject);

#endif // COLLISIONS_H