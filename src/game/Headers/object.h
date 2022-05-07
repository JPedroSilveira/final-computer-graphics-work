#ifndef OBJECT_H
#define OBJECT_H

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <tiny_obj_loader.h>
#include <vector>
#include <map>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>

#include "material.h"

enum {
    MATERIAL=0,
    MATERIAL_GOURAUD,
    GRASS,
    WALL,
};

enum OBJ_TYPE {
    PLAYER=0,
    NPC_OBJ,
    PLAYER_TARGET,
    STATIC
};

enum POSSIBLE_MOV {
    FRONT=0,
    BACK,
    RIGHT,
    LEFT,
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
    glm::vec3 bbox_min;
    glm::vec3 bbox_max;
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
    glm::vec4 move_direction;
    int type;
    int object_type;
    GameObject* father;
    Material material;

    void setMaterial(Material material);
};

struct Player : public GameObject {
    Player(GameObject& object, bool can_move, float speed);
    bool can_move;
    float current_speed;
    float base_speed;
    float move_angle;

    void updateMovement(std::map<POSSIBLE_MOV, bool*> pressed_keys, const float delta_t);
};

struct PlayerTarget : public GameObject {
    PlayerTarget(GameObject& object, bool was_caught);
    bool was_caught;
};

struct NPC : public GameObject {
    NPC(GameObject& object, float t_position, float t_speed, glm::vec4 p0, glm::vec4 p1, glm::vec4 p2, glm::vec4 p3);
    float t_position;
    float t_speed; // ciclos por segundo (volta completa)
    glm::vec4 p0;
    glm::vec4 p1;
    glm::vec4 p2;
    glm::vec4 p3;

    void updateMovement(const float delta_t);
};

#endif // OBJECT_H
