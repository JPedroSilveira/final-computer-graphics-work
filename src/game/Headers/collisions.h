#ifndef _COLLISIONS_H
#define _COLLISIONS_H

#include "object.h"
#include "matrices.h"
#include <math.h> 

bool CollisionCubePlane(GameObject cubeObject, GameObject planObject);
bool CollisionCubeCube(GameObject cubeObjectOne, GameObject cubeObjectTwo);
bool CollisionCubeSphere(GameObject cubeObject, GameObject sphereObject);

#endif // COLLISIONS_H