#include "../Headers/object.h"
// #include "matrices.h"

GameModel::GameModel(const char* filename, const char* object_name, const char* basepath, bool triangulate)
{
    printf("Carregando modelo \"%s\"... ", filename);

    std::string err;
    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, filename, basepath, triangulate);

    if (!err.empty())
        fprintf(stderr, "\n%s\n", err.c_str());

    if (!ret)
        throw std::runtime_error("Erro ao carregar modelo.");

    printf("OK.\n");

    this->go_name = std::string(object_name);
}

GameModel::~GameModel()
{
    //dtor
}


GameObject::GameObject(std::string name, GameModel& model, glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, GameObject* father)
 : name(name), model(model), position(position), scale(scale), rotation(rotation), father(father) {}
