#include <us/Scene.hpp>

#include <iostream>

void Scene::addActor(ActorPtr actor)
{
    if(!actor)
    {
        auto error = "Actor cannot be nullptr";
        std::cerr << error << std::endl;
        throw new std::invalid_argument(error);
    }
    
    actors.push_back(actor);
}