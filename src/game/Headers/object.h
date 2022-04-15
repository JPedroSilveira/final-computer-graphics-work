#ifndef OBJECT_H
#define OBJECT_H

#include <cstdio>
#include <cstdlib>
#include <tiny_obj_loader.h>
#include <vector>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>

enum {
    CHICKEN=0,
    BUNNY,
    PLANE
};

// Estrutura para carregar o modelo
struct GameModel
{
    GameModel(const char* filename, const char* go_name = NULL, const char* basepath = NULL, bool triangulate = true);
    virtual ~GameModel();
    tinyobj::attrib_t                 attrib;
    std::vector<tinyobj::shape_t>     shapes;
    std::vector<tinyobj::material_t>  materials;
    std::string go_name;
};

// Estrutura para, dado um modelo, criar um objeto na cena
struct GameObject {
    GameObject(std::string name, GameModel& model, glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, GameObject* father=nullptr);
    std::string name;
    GameModel& model;
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 rotation;
    int type;
    GameObject* father;
};

#endif // OBJECT_H
