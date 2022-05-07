// Copyright (c) 2021 Rayvant. All rights reserved.

#define GLM_FORCE_SSE42
#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <vector>
#include <chrono>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include <stb_image_write.h>

#include "Ray.h"
#include "HittableList.h"
#include "Sphere.h"
#include "Utilities.h"

vec3 ray_color(const Ray& r, const Hittable& world)
{
	HitRecord rec;
	if (world.Hit(r, 0, infinity, rec))
	{
		return 0.5f * (rec.normal + vec3(1, 1, 1));
	}

	vec3 unit_direction = normalize(r.direction());
	auto t = 0.5f * (unit_direction.y + 1.0f);

	return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
}

int main()
{
	// Image
	const auto aspect_ratio = 16.0 / 9.0;
	const int image_width = 1920;
	const int image_height = static_cast<int>(image_width / aspect_ratio);

	// World
	HittableList world;
	world.Add(make_shared<Sphere>(vec3(0.0f, 0.0f, -1.0f), 0.5f));
	world.Add(make_shared<Sphere>(vec3(0.0f, -100.5f, -1.0f), 100.0f));

	// Camera
	auto viewport_height = 2.0;
	auto viewport_width = aspect_ratio * viewport_height;
	auto focal_length = 1.0;

	auto origin = vec3(0, 0, 0);
	auto horizontal = vec3(viewport_width, 0, 0);
	auto vertical = vec3(0, viewport_height, 0);
	auto lower_left_corner = origin - horizontal / 2.0f - vertical / 2.0f - vec3(0, 0, focal_length);

	auto start = std::chrono::high_resolution_clock::now();

	std::vector<uint8_t> image_data;

	for (int j = image_height - 1; j >= 0; --j)
	{
		std::cout << "\rScanlines remaining: " << j << ' ' << std::flush;

		for (int i = 0; i < image_width; ++i)
		{
			auto u = float(i) / (image_width - 1);
			auto v = float(j) / (image_height - 1);

			Ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
			vec3 pixel_color = ray_color(r, world);

			// write_color function.
			int ir = static_cast<int>(255.999 * pixel_color.x);
			int ig = static_cast<int>(255.999 * pixel_color.y);
			int ib = static_cast<int>(255.999 * pixel_color.z);

			image_data.push_back(ir);
			image_data.push_back(ig);
			image_data.push_back(ib);
		}
	}

	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << "\nTook " << duration.count() << " milliseconds" << std::endl;

	int result = stbi_write_png("Arnold.png", image_width, image_height, 3, image_data.data(), image_width * 3);
	std::cout << "\nDone.\n";
}
