#pragma once


#include <glimac/SDLWindowManager.hpp>
#include <us/Scene.hpp>
#include <us/Renderer.hpp>

#include <memory>

class Application
{
public :

    virtual void run() final;

    virtual ~Application();

protected:
    Application(uint32_t pWindowWidth, uint32_t pWindowHeight, const char* pWindowTitle);

    Application() = delete;

    virtual void processInputs(SDL_Event e) = 0; // <----------- user defined

    virtual void update() = 0; // <----------- user defined

    virtual void render() final;

	std::shared_ptr<glimac::SDLWindowManager> windowManager;
    Renderer renderer;
    Scene scene;
};
using ApplicationPtr = std::shared_ptr<Application>;