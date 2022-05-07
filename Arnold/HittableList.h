#pragma once

#include "Hittable.h"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class HittableList : public Hittable
{
public:
	HittableList() {}
	HittableList(shared_ptr<Hittable> object) { Add(object); }

	void Clear() { objects.clear(); }
	void Add(shared_ptr<Hittable> object) { objects.push_back(object); }

	virtual bool Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override
	{
		HitRecord temp_rec;
		bool hit_anything = false;
		auto closest_so_far = t_max;

		for (const auto& object : objects)
		{
			if (object->Hit(r, t_min, closest_so_far, temp_rec))
			{
				hit_anything = true;
				closest_so_far = temp_rec.t;
				rec = temp_rec;
			}
		}

		return hit_anything;
	}

private:
	std::vector<shared_ptr<Hittable>> objects;
};

