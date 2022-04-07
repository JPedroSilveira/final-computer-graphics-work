#include "../Headers/object.h"

GameObject::GameObject(const char* filename, const char* object_name, const char* basepath, bool triangulate)
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

GameObject::~GameObject()
{
    //dtor
}