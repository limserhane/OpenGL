#pragma once

#include <us/ShadingProgram.hpp>

struct Renderer
{
    ShadingProgramPtr shadingProgram;

    void render(const Scene& scene) const;
};