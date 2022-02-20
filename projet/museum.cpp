
#include <GL/glew.h>

#include <us/Application.hpp>
#include <glimac/Sphere.hpp>
#include <us/ShadingProgram.hpp>
#include <us/FreeflyCamera.hpp>
#include <us/Mesh.hpp>
#include <us/Scene.hpp>
#include <us/Material.hpp>
#include <us/Actor.hpp>
#include <us/Texture.hpp>
#include "Moon.hpp"

#include <vector>
#include <iostream>
#include <string>

using namespace glm;

const std::string BASE_TEXTURE_PATH("/mnt/2E1C47BA1C477C39/esiee/e5/opengl/projet/assets/textures/");
const std::string BASE_OBJ_PATH("/mnt/2E1C47BA1C477C39/esiee/e5/opengl/projet/assets/models/");

#define TEXTURE_PATH(filepath) (BASE_TEXTURE_PATH + std::string(filepath)).c_str()
#define OBJ_PATH(filepath) (BASE_OBJ_PATH + std::string(filepath)).c_str()

class Museum : public Application
{
private:
	FreeflyCameraPtr camera;

	ActorPtr big;
	std::vector<MoonPtr> moons;

public:
	Museum(const glimac::FilePath &applicationPath);
	virtual ~Museum();

private:
	virtual void processInputs(SDL_Event e);
	virtual void update();
};

Museum::Museum(const glimac::FilePath &applicationPath) :
	Application(1280, 720, "Musée"),
	camera(std::make_shared<FreeflyCamera>(70.f, (float)1280 / 720, 0.1f, 100.f))
{
	scene.camera = camera;
	
	renderer.shadingProgram = std::make_shared<ShadingProgram>(applicationPath);

	// ---------------------------------- CONSTANTES ----------------------------
	GeometryPtr cube = loadGeometry(OBJ_PATH("cube.obj"));

	GeometryPtr debugCube = copyGeometry(cube);
	debugCube->get("cube").material->Kd = vec3(1, 0, 0);

	vec3 roomSize(20.f, 5.f, 20.f);
	float wallDepth = 0.1f;

	// ---------------------------------- LIGHTS -----------------------------------
	{
		float lightSpace = 0.25f;
		float lightHeight = 0.9f;
		vec3 lightIntensity = 0.1f * vec3(1.f);
		scene.pointLights.add(vec3(lightSpace, lightHeight, lightSpace) * roomSize, lightIntensity, 0.001f);
		scene.pointLights.add(vec3(-lightSpace, lightHeight, lightSpace) * roomSize, lightIntensity, 0.001f);
		scene.pointLights.add(vec3(lightSpace, lightHeight, -lightSpace) * roomSize, lightIntensity, 0.001f);
		scene.pointLights.add(vec3(-lightSpace, lightHeight, -lightSpace) * roomSize, lightIntensity, 0.001f);

		// scene.directionalLights.add(vec3(1, 1, 1), vec3(0.5f));
	}

	// ----------------------------------- WALLS ------------------------------------------
	{
		GeometryPtr wallCube = copyGeometry(cube);
		GeometryPtr rooftopCube = copyGeometry(cube);
		GeometryPtr floorCube = copyGeometry(cube);

		ActorPtr floor = createActor(floorCube);
		scene.actors.push_back(floor);
		floor->transform.scale = vec3(roomSize.x, wallDepth, roomSize.z);

		ActorPtr backWall = createActor(wallCube);
		scene.actors.push_back(backWall);
		backWall->transform.position = vec3(0.f, roomSize.y / 2, -roomSize.z / 2);
		backWall->transform.scale = vec3(roomSize.x, roomSize.y, wallDepth);

		ActorPtr frontWall = createActor(wallCube);
		scene.actors.push_back(frontWall);
		frontWall->transform.position = vec3(0.f, roomSize.y / 2, roomSize.z / 2);
		frontWall->transform.scale = vec3(roomSize.x, roomSize.y, wallDepth);

		ActorPtr leftWall = createActor(wallCube);
		scene.actors.push_back(leftWall);
		leftWall->transform.position = vec3(-roomSize.x / 2, roomSize.y / 2, 0.f);
		leftWall->transform.scale = vec3(wallDepth, roomSize.y, roomSize.z);

		ActorPtr rightWall = createActor(wallCube);
		scene.actors.push_back(rightWall);
		rightWall->transform.position = vec3(roomSize.x / 2, roomSize.y / 2, 0.f);
		rightWall->transform.scale = vec3(wallDepth, roomSize.y, roomSize.z);
	}

	// --------------------------------- ACTORS -----------------------------------------

	// Paints
	{
		TexturePtr trimSheet = loadTexture(TEXTURE_PATH("paints/trimsheet.png"));
		TexturePtr woodTexture = loadTexture(TEXTURE_PATH("wood.png"));

		ActorPtr joconde = createActor(loadGeometry(OBJ_PATH("paints/joconde.obj")));
		scene.addActor(joconde);
		joconde->geometry->get("paint").material->Tex = trimSheet;
		joconde->geometry->get("frame").material->Tex = woodTexture;
		joconde->geometry->get("frame").material->Ks = vec3(1.f);
		joconde->transform.position = vec3(0.f, 2.f, -0.99f * roomSize.z / 2);
		joconde->transform.rotation.y = 180.f;
		joconde->transform.scale = vec3(0.02f);
		scene.pointLights.add(vec3(joconde->transform.position.x, joconde->transform.position.y + 0.f, joconde->transform.position.z + 0.8f), vec3(1), 1);

		ActorPtr venus = createActor(loadGeometry(OBJ_PATH("paints/venus.obj")));
		scene.addActor(venus);
		venus->geometry->get("paint").material->Tex = trimSheet;
		venus->geometry->get("frame").material->Tex = woodTexture;
		joconde->geometry->get("frame").material->Ks = vec3(1.f);
		venus->transform.position = vec3(-5.f, 2.f, -0.99f * roomSize.z / 2);
		venus->transform.rotation.y = 180.f;
		venus->transform.scale = vec3(0.02f);
		scene.pointLights.add(vec3(venus->transform.position.x, venus->transform.position.y + 0.f, venus->transform.position.z + 0.8f), vec3(1), 1);

		ActorPtr kanagawa = createActor(loadGeometry(OBJ_PATH("paints/kanagawa.obj")));
		scene.addActor(kanagawa);
		kanagawa->geometry->get("paint").material->Tex = trimSheet;
		kanagawa->geometry->get("frame").material->Tex = woodTexture;
		joconde->geometry->get("frame").material->Ks = vec3(1.f);
		kanagawa->transform.position = vec3(5.f, 2.f, -0.99f * roomSize.z / 2);
		kanagawa->transform.rotation.y = 180.f;
		kanagawa->transform.scale = vec3(0.02f);
		scene.pointLights.add(vec3(kanagawa->transform.position.x, kanagawa->transform.position.y + 0.f, kanagawa->transform.position.z + 0.8f), vec3(1), 1);

		ActorPtr bench = createActor(loadGeometry(OBJ_PATH("bench.obj")));
		scene.addActor(bench);
		bench->geometry->get("bench").material->Ks = vec3(1);
		bench->geometry->get("bench").material->Shininess = 256.f;
		bench->transform.position.z = -roomSize.z / 2 + 7.f;
		bench->transform.rotation.y = -90.f;
	}

	// Statues
	{
		ActorPtr statue = createActor(loadGeometry(OBJ_PATH("statues/0.obj")));
		statue->geometry->get("statue").material->Tex = loadTexture(TEXTURE_PATH("statues/0.jpg"));
		statue->geometry->get("statue").material->Ks = vec3(0.135000f);
		scene.addActor(statue);
		statue->transform.position = vec3(-0.8f * roomSize.x / 2.f, 0.f, 0.f);
		statue->transform.rotation.y = 90.f;
		scene.pointLights.add(vec3(statue->transform.position.x + 0.8f, statue->transform.position.y + 1.6f, statue->transform.position.z), vec3(1.5f), 1);
		scene.pointLights.add(vec3(statue->transform.position.x - 0.8f, statue->transform.position.y + 1.6f, statue->transform.position.z), vec3(0.6), 1);

		ActorPtr statue1 = createActor(loadGeometry(OBJ_PATH("statues/1.obj")));
		statue1->geometry->get("statue").material->Tex = loadTexture(TEXTURE_PATH("statues/1.jpg"));
		statue1->geometry->get("statue").material->Ks = vec3(0.135000f);
		scene.addActor(statue1);
		statue1->transform.position = vec3(-0.8f * roomSize.x / 2.f, 0.f, -5.f);
		statue1->transform.rotation.y = 90.f;
		scene.pointLights.add(vec3(statue1->transform.position.x + 0.8f, statue1->transform.position.y + 1.6f, statue1->transform.position.z), vec3(1.5f), 1);
		scene.pointLights.add(vec3(statue1->transform.position.x - 0.8f, statue1->transform.position.y + 1.6f, statue1->transform.position.z), vec3(0.6), 1);

		ActorPtr statue2 = createActor(loadGeometry(OBJ_PATH("statues/2.obj")));
		statue2->geometry->get("body").material->Tex = loadTexture(TEXTURE_PATH("statues/2body.jpg"));
		statue2->geometry->get("body").material->Ks = vec3(0.135000f);
		statue2->geometry->get("pedestal").material->Tex = loadTexture(TEXTURE_PATH("statues/2pedestal.jpg"));
		statue2->geometry->get("pedestal").material->Ks = vec3(0.135000f);
		scene.addActor(statue2);
		statue2->transform.position = vec3(-0.8f * roomSize.x / 2.f, 0.f, 5.f);
		statue2->transform.rotation.y = 90.f;
		scene.pointLights.add(vec3(statue2->transform.position.x + 0.8f, statue2->transform.position.y + 0.6f, statue2->transform.position.z + 0.2f), vec3(1.f), 1);
		scene.pointLights.add(vec3(statue2->transform.position.x - 0.8f, statue2->transform.position.y + 1.8f, statue2->transform.position.z), vec3(0.6), 1);
	}

	GeometryPtr rock = loadGeometry(OBJ_PATH("rock.obj"));
	rock->get("rock").material->Tex = loadTexture(TEXTURE_PATH("rock/texture.png"));
	rock->get("rock").material->NormalMap = loadTexture(TEXTURE_PATH("rock/nmap.png"));
	rock->get("rock").material->Kd = vec3(1.f);
	rock->get("rock").material->Ks = vec3(0.5f);
	rock->get("rock").material->Shininess = 128;
	
	big = createActor(rock);
	scene.addActor(big);
	big->transform.position = vec3(roomSize.x / 2 - 4.f, 1.f, roomSize.z / 2 - 4.f);
	scene.pointLights.add(vec3(big->transform.position.x , big->transform.position.y + 1.f, big->transform.position.z), vec3(1.5f), 1);
	scene.pointLights.add(vec3(big->transform.position.x - 2.f, big->transform.position.y + 0.5f, big->transform.position.z + 1.f), vec3(1.5f), 1);
	scene.pointLights.add(vec3(big->transform.position.x +
	 1.f, big->transform.position.y + 1.f, big->transform.position.z - 2.f), vec3(1.5f), 1);

	// Moons
	{
		for(auto i = 0; i < 30; ++i)
		{
			MoonPtr moon = createMoon(rock, vec3(0), 25.f);
			scene.addActor(moon);
			moons.push_back(moon);
			moon->transform.scale = vec3(1.f);
		}
	}
}

Museum::~Museum()
{
}

void Museum::processInputs(SDL_Event e)
{
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			camera->setLeftRotation(2.f);
			break;
		case SDLK_RIGHT:
			camera->setLeftRotation(-2.f);
			break;
		case SDLK_UP:
			camera->setUpRotation(2.f);
			break;
		case SDLK_DOWN:
			camera->setUpRotation(-2.f);
			break;
		case SDLK_z:
			camera->setFrontMove(0.2f);
			break;
		case SDLK_s:
			camera->setFrontMove(-0.2f);
			break;
		case SDLK_a:
			camera->setLeftMove(0.2f);
			break;
		case SDLK_e:
			camera->setLeftMove(-0.2f);
			break;
		case SDLK_SPACE:
			camera->setUpMove(0.2f);
			break;
		case SDLK_x:
			camera->setUpMove(-0.2f);
			break;
		}
		break;
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			camera->setLeftRotation(0.f);
			break;
		case SDLK_RIGHT:
			camera->setLeftRotation(0.f);
			break;
		case SDLK_UP:
			camera->setUpRotation(0.f);
			break;
		case SDLK_DOWN:
			camera->setUpRotation(0.f);
			break;
		case SDLK_z:
			camera->setFrontMove(0.f);
			break;
		case SDLK_s:
			camera->setFrontMove(0.f);
			break;
		case SDLK_a:
			camera->setLeftMove(0.f);
			break;
		case SDLK_e:
			camera->setLeftMove(0.f);
			break;
		case SDLK_SPACE:
			camera->setUpMove(0.f);
			break;
		case SDLK_x:
			camera->setUpMove(0.f);
			break;
		}
		break;
	}
}

void Museum::update()
{
	camera->update();

	big->transform.rotation.y += 0.05f;

	for(MoonPtr moon : moons) moon->update(windowManager->getTime());
}

int main(int argc, char **argv)
{
	glimac::FilePath applicationPath(argv[0]);

	Museum *app = new Museum(applicationPath);
	app->run();
	delete app;

	return 0;
}