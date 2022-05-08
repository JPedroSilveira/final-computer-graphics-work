#version 330 core

// Atributos de fragmentos recebidos como entrada ("in") pelo Fragment Shader.
// Neste exemplo, este atributo foi gerado pelo rasterizador como a
// interpolação da posição global e a normal de cada vértice, definidas em
// "shader_vertex.glsl" e "main.cpp".
in vec4 position_world;
in vec4 normal;

in vec4 color_v;

// Coordenadas de textura obtidas do arquivo OBJ (se existirem!)
in vec2 texcoords;

// Matrizes computadas no código C++ e enviadas para a GPU
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// Parâmetros da axis-aligned bounding box (AABB) do modelo
uniform vec4 bbox_min;
uniform vec4 bbox_max;


// Identificador que define qual objeto está sendo desenhado no momento
#define MATERIAL 0 // Calcula apenas o material
#define MATERIAL_GOURAUD 1 // Calcula apenas o material
#define GRASS 2  // Usa textura de grama no objeto
#define WALL  3 // Usa a textura de parede
#define CHICKEN 4 // Usa a textura de galinha

uniform int object_id;

// Texturas utilizadas
uniform sampler2D Grass;
uniform sampler2D GreenWall;
uniform sampler2D Chicken;

// Caso de use material, recebe esses valores do Modelo
struct Material {
    vec3 Kd;
    vec3 Ks;
    vec3 Ka;
    float q;
};

// Material recebido pelo programa
uniform Material material;

// O valor de saída ("out") de um Fragment Shader é a cor final do fragmento.
out vec4 color;

void main()
{
    // Obtemos a posição da câmera utilizando a inversa da matriz que define o
    // sistema de coordenadas da câmera.
    vec4 origin = vec4(0.0, 0.0, 0.0, 1.0);
    vec4 camera_position = inverse(view) * origin;

    // O fragmento atual é coberto por um ponto que percente à superfície de um
    // dos objetos virtuais da cena. Este ponto, p, possui uma posição no
    // sistema de coordenadas global (World coordinates). Esta posição é obtida
    // através da interpolação, feita pelo rasterizador, da posição de cada
    // vértice.
    vec4 p = position_world;

    // Normal do fragmento atual, interpolada pelo rasterizador a partir das
    // normais de cada vértice.
    vec4 n = normalize(normal);

    // Vetor que define o sentido da fonte de luz em relação ao ponto atual.
    vec4 l = normalize(vec4(1.0,1.0,0.5,0.0));

    // Vetor que define o sentido da câmera em relação ao ponto atual.
    vec4 v = normalize(camera_position - p);

    // Vetor h para modelo de blinn-phong
    vec4 h = normalize(l + v);

    // Espectro da fonte de iluminação
    vec3 I = vec3(1.0,1.0,1.0);
    // Espectro da luz ambiente
    vec3 Ia = vec3(0.1, 0.1, 0.1);

    if (object_id == MATERIAL)
    {
        // Termo difuso utilizando a lei dos cossenos de Lambert
        vec3 lambert_diffuse_term = material.Kd * I * max(0, dot(n, l));
        // Termo ambiente
        vec3 ambient_term = material.Ka * Ia;
        // Termo especular utilizando o modelo de iluminação de Blinn-Phong
        vec3 phong_specular_term  = material.Ks * I * pow(max(0, dot(h, n)), material.q);
        // Alpha
        color.a = 1;
        // Cor final do fragmento calculada com uma combinação dos termos difuso,
        // especular, e ambiente. Veja slide 129 do documento Aula_17_e_18_Modelos_de_Iluminacao.pdf.
        color.rgb = lambert_diffuse_term + ambient_term + phong_specular_term;
    }
    // Chão por UV Mapping
    else if (object_id == GRASS)
    {
        // Coordenadas de textura do plano, obtidas do arquivo OBJ.
        float U = texcoords.x;
        float V = texcoords.y;

        vec3 Kd0 = texture(Grass, vec2(U,V)).rgb;

        // Equação de Iluminação
        float lambert = max(0,dot(n,l));
        color.rgb = Kd0 * (lambert + 0.01);
        color.a = 1;
    }
    // Parede por UV mapping
    else if (object_id == WALL)
    {
        // Coordenadas de textura do plano, obtidas do arquivo OBJ.
        float U = texcoords.x;
        float V = texcoords.y;

        vec3 Kd0 = texture(GreenWall, vec2(U,V)).rgb;

        // Equação de Iluminação
        float lambert = max(0,dot(n,l));
        color.rgb = Kd0 * (lambert + 0.5);
        color.a = 1;
    }
    // Galinha por UV Mapping
    // mistura mapeamento de textura com blinn-phong
    // para dar um aspecto brilhante nas penas
    else if (object_id == CHICKEN)
    {
        // Coordenadas de textura do plano, obtidas do arquivo OBJ.
        float U = texcoords.x;
        float V = texcoords.y;
        // Obtemos a refletância difusa a partir da leitura da imagem TextureImage0
        vec3 Kd0 = texture(Chicken, vec2(U,V)).rgb;
        vec3 lambert_diffuse_term = Kd0 * (max(0,dot(n,l)));

        vec3 ambient_term = material.Ka * Ia;
        // Termo especular utilizando o modelo de iluminação de Blinn-Phong
        vec3 phong_specular_term  = material.Ks * I * pow(max(0, dot(h, n)), material.q);
        color.rgb = lambert_diffuse_term + ambient_term + phong_specular_term;
        color.a = 1;
    }
    // Material padrão: puxa cor do vertex shader
    else // if (object_id == MATERIAL_GOURAUD) ou sem definir
    {
        color = color_v;
    }

    

    // Cor final com correção gamma, considerando monitor sRGB.
    // Veja https://en.wikipedia.org/w/index.php?title=Gamma_correction&oldid=751281772#Windows.2C_Mac.2C_sRGB_and_TV.2Fvideo_standard_gammas
    color.rgb = pow(color.rgb, vec3(1.0,1.0,1.0)/2.2);
} 
