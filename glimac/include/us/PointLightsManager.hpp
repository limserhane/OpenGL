#pragma once

#include <glimac/glm.hpp>

#include <vector>
#include <memory>

using namespace glm;

struct PointLightsManager
{
    std::vector<vec3> positions;
    std::vector<vec3> intensities;
    std::vector<float> attenuations;

    PointLightsManager() = default;

    void add(vec3 pPosition, vec3 pIntensity, float pAttenuation = 1);

    unsigned getCount() const { return positions.size();}
};
using PointLightsManagerPtr = std::shared_ptr<PointLightsManager>;