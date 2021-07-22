#pragma once

#include <glm/vec3.hpp>

using namespace glm;

class Ray
{
public:
	Ray() : orig(0), dir(0) {}

	Ray(const vec3& origin, const vec3& direction)
		: orig(origin), dir(direction) {}

	vec3 origin() const { return orig; }
	vec3 direction() const { return dir; }

	vec3 at(float t) const { return orig + t * dir; }

private:
	vec3 orig;
	vec3 dir;
};

