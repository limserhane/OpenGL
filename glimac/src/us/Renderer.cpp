#include <us/Renderer.hpp>


void Renderer::render(const Scene& scene) const
{
    shadingProgram->render(scene);
}