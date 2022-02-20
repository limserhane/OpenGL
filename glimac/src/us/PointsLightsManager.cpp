#include <us/PointLightsManager.hpp>


void PointLightsManager::add(vec3 pPosition, vec3 pIntensity, float pAttenuation)
{
    positions.push_back(pPosition);
    intensities.push_back(pIntensity);
    attenuations.push_back(pAttenuation);
}