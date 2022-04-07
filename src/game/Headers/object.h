#ifndef OBJECT_H
#define OBJECT_H

#include <cstdio>
#include <cstdlib>
#include <tiny_obj_loader.h>
#include <vector>
#include <glm/vec4.hpp>

struct GameObject
{
    GameObject(const char* filename, const char* go_name = NULL, const char* basepath = NULL, bool triangulate = true);
    virtual ~GameObject();
    tinyobj::attrib_t                 attrib;
    std::vector<tinyobj::shape_t>     shapes;
    std::vector<tinyobj::material_t>  materials;
    std::string go_name;

    void ComputeNormals();
};

struct Player : public GameObject
{

};

#endif // OBJECT_H
