#pragma once

#include <us/Transform.hpp>
#include <us/TrackballCamera.hpp>
#include <us/Geometry.hpp>

#include <memory>

struct Actor
{
    Transform transform;
    GeometryPtr geometry;

    Actor();
    Actor(GeometryPtr pGeometry);
    
};
using ActorPtr = std::shared_ptr<Actor>;

ActorPtr createActor(GeometryPtr geometry);