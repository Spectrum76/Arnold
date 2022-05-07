#pragma once

#include <glm/gtx/norm.hpp>

#include "Hittable.h"

class Sphere : public Hittable
{
public:
	Sphere() : center(0), radius(0) {}
	Sphere(vec3 cen, float r) : center(cen), radius(r) {}

	virtual bool Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override
	{
		vec3 oc = r.origin() - center;
		auto a = length2(r.direction());
		auto half_b = dot(oc, r.direction());
		auto c = length2(oc) - radius * radius;

		auto discriminant = half_b * half_b - a * c;
		if (discriminant < 0) return false;
		auto sqrtd = sqrt(discriminant);

		// Find the nearest root that lies in the acceptable range.
		auto root = (-half_b - sqrtd) / a;
		if (root < t_min || t_max < root)
		{
			root = (-half_b + sqrtd) / a;
			if (root < t_min || t_max < root)
				return false;
		}

		rec.t = root;
		rec.p = r.at(rec.t);
		rec.normal = (rec.p - center) / radius;

		vec3 outward_normal = (rec.p - center) / radius;
		rec.set_face_normal(r, outward_normal);

		return true;
	}

private:
	vec3 center;
	float radius;
};

