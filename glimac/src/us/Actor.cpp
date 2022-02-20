#include <us/Actor.hpp>

#include <glimac/glm.hpp>

using namespace glm;

Actor::Actor():
    transform(),
    geometry(nullptr)
{}

Actor::Actor(GeometryPtr pGeometry):
    transform(),
    geometry(pGeometry)
{}

ActorPtr createActor(GeometryPtr geometry)
{
    return std::make_shared<Actor>(geometry);
}