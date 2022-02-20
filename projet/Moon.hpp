#pragma once

#include <glimac/glm.hpp>
#include <us/Actor.hpp>
#include <us/Geometry.hpp>

using namespace glm;

struct Moon : public Actor
{
    vec3 parameter1;
    vec3 parameter2;

    vec3 center;

    Moon(GeometryPtr pGeometry, vec3 pCenter, float pRadius):
        Actor(pGeometry),
        center(pCenter),
        parameter1(sphericalRand(pRadius)),
        parameter2(sphericalRand(pRadius))
    {}
    
    void update(float time)
    {
		float angle = 0.5f * time;

		mat4 orbit;
		orbit = translate(mat4(1.f), center);
		orbit = rotate(orbit, angle, cross(parameter1, parameter2));
		orbit = translate(orbit, parameter1);

		vec4 position = orbit * vec4(0.f, 0.f, 0.f, 1.f);

		transform.position = vec3(position.x, position.y, position.z);
	}
};
using MoonPtr = std::shared_ptr<Moon>;

MoonPtr createMoon(GeometryPtr pGeometry, vec3 pCenter, float pRadius)
{
    return std::make_shared<Moon>(pGeometry, pCenter, pRadius);
}