#include "TerrainGenerator.h"
#include "FastNoiseLite.h"
#include <assert.h>

TerrainGenerator* TerrainGenerator::sInstance = nullptr;

TerrainGenerator::TerrainGenerator()
{
	//only allow one TerrainGenerator to exist
	assert(sInstance == nullptr);
	sInstance = this;
}

module::Perlin gen; // if using libnoise
double noise(double nx, double ny) { // if using libnoise
	// Rescale from -1.0:+1.0 to 0.0:1.0
	return gen.GetValue(nx, ny, 0) / 2.0 + 0.5;
}

FastNoiseLite gen; // if using fastnoiselite
double noise(double nx, double ny) { // if using fastnoiselite
	// Rescale from -1.0:+1.0 to 0.0:1.0
	return gen.GetNoise(nx, ny) / 2.0 + 0.5;
}

double value[height][width];
for (int y = 0; y < height; y++) {
	for (int x = 0; x < width; x++) {
		double nx = x / width - 0.5,
			ny = y / height - 0.5;
		value[y][x] = noise(nx, ny);
	}
}