#pragma once

#include <glimac/glm.hpp>

#include <vector>
#include <memory>

using namespace glm;

struct DirectionalLightsManager
{
    std::vector<vec3> directions;
    std::vector<vec3> intensities;

    DirectionalLightsManager() = default;

    void add(vec3 pDirection, vec3 pIntensity);

    unsigned getCount() const { return directions.size();}

    vec3& getDirection(unsigned index);
    vec3 getDirection(unsigned index) const;
    void setDirection(unsigned index, vec3 pDirection);

    vec3& getIntensity(unsigned index);
    vec3 getIntensity(unsigned index) const;
    void setIntensity(unsigned index, vec3 pIntensity);
};
using DirectionalLightsManagerPtr = std::shared_ptr<DirectionalLightsManager>;