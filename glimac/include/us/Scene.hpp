#pragma once

#include <us/FreeflyCamera.hpp>
#include <us/Actor.hpp>
#include <us/DirectionalLightsManager.hpp>
#include <us/PointLightsManager.hpp>
#include <vector>
#include <memory>

struct Scene
{
    FreeflyCameraPtr camera;

    std::vector<ActorPtr> actors;

    DirectionalLightsManager directionalLights;
    PointLightsManager pointLights;

    Scene() = default;

    void addActor(ActorPtr actor);
};
using ScenePtr = std::shared_ptr<Scene>;