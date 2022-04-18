#ifndef OBJECT_H
#define OBJECT_H

#include <cstdio>
#include <cstdlib>
#include <tiny_obj_loader.h>
#include <vector>
#include <map>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>

enum {
    CHICKEN=0,
    BUNNY,
    PLANE
};

enum POSSIBLE_MOV {
    X_UP=0,
    X_DOWN,
    Z_UP,
    Z_DOWN,
    SPEED_UP,
    SPEED_DOWN,
    JUMP
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
    GameObject(std::string name, GameModel& model, glm::vec4 position, glm::vec3 scale, glm::vec3 rotation, GameObject* father=nullptr);
    std::string name;
    GameModel& model;
    glm::vec4 position;
    glm::vec3 scale;
    glm::vec3 rotation;
    int type;
    GameObject* father;
};

struct Player : public GameObject {
    Player(GameObject& object, bool can_move, float speed);
    bool can_move;
    float current_speed;
    float base_speed;

    void updateMovement(std::map<POSSIBLE_MOV, bool*> pressed_keys, const float delta_t);
};

#endif // OBJECT_H
