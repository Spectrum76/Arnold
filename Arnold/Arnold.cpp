// Copyright (c) 2021 Rayvant. All rights reserved.

#define GLM_FORCE_SSE42
#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <vector>
#include <chrono>
#include <iostream>

#include <glm/glm.hpp>
#include <spdlog/spdlog.h>
#include <stb_image_write.h>

int main()
{
	const int image_width = 1280;
	const int image_height = 720;

	std::vector<uint8_t> image_data;

	for (int j = image_height - 1; j >= 0; --j)
	{
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;

		for (int i = 0; i < image_width; ++i)
		{
			auto r = float(i) / (image_width - 1);
			auto g = float(j) / (image_height - 1);
			auto b = 0.25f;

			int ir = static_cast<int>(255.999 * r);
			int ig = static_cast<int>(255.999 * g);
			int ib = static_cast<int>(255.999 * b);

			image_data.push_back(ir);
			image_data.push_back(ig);
			image_data.push_back(ib);
		}
	}

	int result = stbi_write_png("Arnold.png", image_width, image_height, 3, image_data.data(), image_width * 3);
	std::cerr << "\nDone.\n";
}
