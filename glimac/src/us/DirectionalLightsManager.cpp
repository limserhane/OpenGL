#include <us/DirectionalLightsManager.hpp>


void DirectionalLightsManager::add(vec3 pDirection, vec3 pIntensity)
{
    directions.push_back(pDirection);
    intensities.push_back(pIntensity);
}
    
vec3& DirectionalLightsManager::getDirection(unsigned index)
{
    return directions[index];
}

vec3 DirectionalLightsManager::getDirection(unsigned index) const
{
    return directions[index];
}

void DirectionalLightsManager::setDirection(unsigned index, vec3 pDirection)
{
    directions[index] = pDirection;
}

vec3& DirectionalLightsManager::getIntensity(unsigned index)
{
    return intensities[index];
}

vec3 DirectionalLightsManager::getIntensity(unsigned index) const
{
    return intensities[index];
}

void DirectionalLightsManager::setIntensity(unsigned index, vec3 pIntensity)
{
    intensities[index] = pIntensity;
}