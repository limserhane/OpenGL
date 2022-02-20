#include <us/Material.hpp>


Material::Material():
    Kd(1),
    Ks(0),
    Shininess(16),
    Tex(nullptr),
    NormalMap(nullptr)
{}

Material::Material(const Material& pOther):
    Kd(pOther.Kd),
    Ks(pOther.Ks),
    Shininess(pOther.Shininess),
    Tex(pOther.Tex),
    NormalMap(pOther.NormalMap)
{}

Material& Material::operator=(const Material& pOther)
{
    this->Kd = pOther.Kd;
    this->Ks = pOther.Ks;
    this->Shininess = pOther.Shininess;
    this->Tex = pOther.Tex;
    this->NormalMap = pOther.NormalMap;

    return *this;
}