#include <us/Application.hpp>

#include <GL/glew.h>
#include <iostream>
#include <chrono>



Application::Application(uint32_t pWindowWidth, uint32_t pWindowHeight, const char* pWindowTitle):
    windowManager(std::make_shared<glimac::SDLWindowManager>(pWindowWidth, pWindowHeight, pWindowTitle)),
	scene()
{
	GLenum glewInitError = glewInit();
	if(GLEW_OK != glewInitError) {
		std::cerr << glewGetErrorString(glewInitError) << std::endl;
		throw new std::runtime_error("GLEW init failure");
	}

	std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

	glEnable(GL_DEPTH_TEST);
}

Application::~Application()
{}

void Application::render()
{
	renderer.render(scene);
}

void Application::run()
{
	bool done = false;
	while(!done) {

		SDL_Event e;
		while(windowManager->pollEvent(e)) {
			if(e.type == SDL_QUIT) {
				done = true;
			}
			processInputs(e); // <------------------------
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        update(); // <------------------------

		render();

		windowManager->swapBuffers();
	}
}