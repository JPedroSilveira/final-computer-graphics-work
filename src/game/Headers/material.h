#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/vec3.hpp>

// Tipos para indicar os shaders o que fazer
enum {
    MATERIAL=0, // Calcular cor solida no fragment (Phong / Blinn-Phong)
    MATERIAL_GOURAUD, // Calcular cor solida no vertex (Gouraud / Lambert + ambiente) - PADRÃO
    GRASS, // Textura de Grama (Phong / Lambert)
    WALL, // Textura de Parede Verde (Phong / Lambert)
    CHICKEN, // Textura da galinha (Phong / Blinn-Phong)
};

struct Material {
    glm::vec3 Kd; // Termo Difuso
    glm::vec3 Ks; // Termo Especular
    glm::vec3 Ka; // Termo Ambiente
    float q; // Coeficiente q
};

// Material padrão caso nenhum seja definido
const Material base_material {
    glm::vec3(0.3,0.3,0.3),
    glm::vec3(0.3,0.3,0.3),
    glm::vec3(0.2,0.2,0.2),
    32
};

#endif