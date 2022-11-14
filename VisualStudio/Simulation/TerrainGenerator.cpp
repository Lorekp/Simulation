#include "TerrainGenerator.h"
#include "FastNoiseLite.h"
#include "AssetManager.h"
#include <assert.h>
#include <vector>
#include <SFML/Graphics.hpp>

TerrainGenerator* TerrainGenerator::sInstance = nullptr;

TerrainGenerator::TerrainGenerator()
{
	//only allow one TerrainGenerator to exist
	assert(sInstance == nullptr);
	sInstance = this;
}



double TerrainGenerator::generateMap(int seed, int width, int height) {

	FastNoiseLite gen = FastNoiseLite(seed);
	gen.SetNoiseType(FastNoiseLite::NoiseType_Perlin);

	gen.SetFrequency(0.01f);
	gen.SetFractalLacunarity(2.f);
	gen.SetFractalGain(0.5f);

	gen.SetFractalType(FastNoiseLite::FractalType_FBm);

	std::vector<sf::Texture> noiseData(width*height);
	int index = 0;

	for (int y = 0; y < width; y++)
	{
		for (int x = 0; x < height; x++)
		{
			if (gen.GetNoise(x, y) <= 0.04)
				noiseData.at((y * width) + x) = sf::Texture(AssetManager::GetTexture("")); //Water
			else if (gen.GetNoise(x, y) <= 0.08)
				noiseData.at((y * width) + x) = sf::Texture(AssetManager::GetTexture("")); //Sand
			else
				noiseData.at((y * width) + x) = sf::Texture(AssetManager::GetTexture("")); //Grass
		}
	}
}

