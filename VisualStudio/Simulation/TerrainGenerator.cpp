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

FastNoiseLite gen; // if using fastnoiselite
double noise(double nx, double ny) { // if using fastnoiselite
	// Rescale from -1.0:+1.0 to 0.0:1.0
	return gen.GetNoise(nx, ny) / 2.0 + 0.5;
}