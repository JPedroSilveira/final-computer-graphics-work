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
    // Valores do vetor de movimento
    float r = current_speed;
    float x = r*cos(this->move_angle);
    float z = r*sin(this->move_angle);
    move_direction = glm::vec4(x,0,z,0);

        if (*pressed_keys[FRONT])
        {
            if (can_move){
                this->position += move_direction * current_speed * delta_t;
            } else {
                this->position -= move_direction * 0.025f;
            }
        }
        if (*pressed_keys[BACK])
        {
            if (can_move){
                this->position -= move_direction * current_speed * delta_t;
            } else {
                this->position += move_direction * 0.025f;
            }
        }
    
    // Can change direction without moving
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

NPC::NPC(GameObject& object, float t_position, float t_speed, glm::vec4 p0, glm::vec4 p1, glm::vec4 p2, glm::vec4 p3):
GameObject(object), t_position(t_position), t_speed(t_speed), p0(p0), p1(p1), p2(p2), p3(p3) {}

void NPC::updateMovement(const float delta_t)
{
    t_position += t_speed * delta_t;

    if (t_position > 1) {
        t_position = 1;
        t_speed *= -1; 
    }
    if (t_position < 0) {
        t_position = 0;
        t_speed *= -1; 
    }

    glm::vec4 c01  = p0 + t_position * (p1 - p0);
    glm::vec4 c12  = p1 + t_position * (p2 - p1);
    glm::vec4 c23  = p2 + t_position * (p3 - p2);
    glm::vec4 c012 = c01 + t_position * (c12 - c01);
    glm::vec4 c123 = c12 + t_position * (c23 - c12);
    this->position = c012 + t_position * (c123 - c012); // Nova posição
}