 #include "../Headers/object.h"

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


GameObject::GameObject(std::string name, GameModel& model, glm::vec4 position, glm::vec3 scale, glm::vec3 rotation, GameObject* father)
 : name(name), model(model), position(position), scale(scale), rotation(rotation), move_direction(glm::vec4(1,0,0,0)),
  father(father), material(base_material) {}


void GameObject::setMaterial(Material material)
{
    this->material.Kd = material.Kd;
    this->material.Ks = material.Ks;
    this->material.Ka = material.Ka;
    this->material.q = material.q;
}


Player::Player(GameObject& object, bool can_move, float speed) :
GameObject(object), can_move(can_move), current_speed(speed), base_speed(speed) {
    this->move_angle = 0;
}

void Player::updateMovement(std::map<POSSIBLE_MOV, bool*> pressed_keys, const float delta_t)
{
    if (can_move)
    {
        // Valores do vetor de movimento
        float r = current_speed;
        float x = r*cos(this->move_angle);
        float z = r*sin(this->move_angle);
        move_direction = glm::vec4(x,0,z,0);

        if (*pressed_keys[FRONT])
        {
            this->position += move_direction * current_speed * delta_t;
        }
        if (*pressed_keys[BACK])
        {
            this->position -= move_direction * current_speed * delta_t;
        }
        if (*pressed_keys[RIGHT])
        {
            this->rotation.y -= current_speed * delta_t;
            this->move_angle += current_speed * delta_t;
        }
        if (*pressed_keys[LEFT])
        {
            this->rotation.y += current_speed * delta_t;
            this->move_angle -= current_speed * delta_t;

        }
    }
}