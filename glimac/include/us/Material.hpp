#pragma once

#include <glimac/glm.hpp>

#include <us/Texture.hpp>

#include <glimac/glm.hpp>
#include <memory>

using namespace glm;

struct Material
{
    vec3 Kd;
    vec3 Ks;
    float Shininess;
    TexturePtr Tex;
    TexturePtr NormalMap;

    Material();
    Material(const Material& pOther);
    Material& operator=(const Material& pOther);
};
using MaterialPtr = std::shared_ptr<Material>;
