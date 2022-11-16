#include "TerrainGenerator.h"
#include "FastNoiseLite.h"
#include "AssetManager.h"
#include <assert.h>

TerrainGenerator* TerrainGenerator::sInstance = nullptr;

TerrainGenerator::TerrainGenerator()
{
	//only allow one TerrainGenerator to exist
	assert(sInstance == nullptr);
	sInstance = this;
}

std::vector<int> TerrainGenerator::generateNoiseMap(int seed, int width, int height) {

	FastNoiseLite gen = FastNoiseLite(seed);
	gen.SetNoiseType(FastNoiseLite::NoiseType_Perlin);

    gen.SetFrequency(0.02f);
	gen.SetFractalLacunarity(2.f);
	gen.SetFractalGain(0.5f);

	gen.SetFractalType(FastNoiseLite::FractalType_FBm);

	std::vector<int> noiseData(width*height);
	int index = 0;

	for (int y = 0; y < width; y++)
	{
		for (int x = 0; x < height; x++)
		{
			float noiseType = gen.GetNoise((float)x, (float)y);

			if (noiseType <= 0.04)
				noiseData.at((y * width) + x) = 0; //Water
			else if (noiseType <= 0.08)
				noiseData.at((y * width) + x) = 1; //Sand
			else
				noiseData.at((y * width) + x) = 2; //Grass
		}
	}

	return noiseData;
}

sf::Sprite TerrainGenerator::generateMap(sf::RenderWindow& window, int width, int height, sf::RenderTexture& terrain, float seed)
{
    //setup tiles
    sf::Sprite waterTile;
    sf::Sprite sandTile;
    sf::Sprite grassTile;
    waterTile.setTexture(AssetManager::GetTexture("Textures/Environment/water1.png"));
    sandTile.setTexture(AssetManager::GetTexture("Textures/Environment/sandClear.png"));
    grassTile.setTexture(AssetManager::GetTexture("Textures/Environment/grassClear.png"));


    //Background setup
    terrain.create(window.getSize().y, window.getSize().x);
    terrain.clear();

    std::vector<int> genMap = TerrainGenerator::generateNoiseMap(seed, width, height);
    //make a background texture out of the single tiles
    float tilePosX = 0;
    float tilePosY = 0;
    for (int i = 0; i < width * height; i++)
    {
        int tileType = genMap.at(i);
        if ((i % width != 0) && (i != 0)) //while not at the end of row do:
            tilePosX = tilePosX + 16;
        else if (i != 0)//last tile of the row
        {
            tilePosY = tilePosY + 16;
            tilePosX = 0;
        }
        if (tileType == 0)
        {
            waterTile.setPosition(tilePosX, tilePosY);
            terrain.draw(waterTile);
        }
        else if (tileType == 1)
        {
            sandTile.setPosition(tilePosX, tilePosY);
            terrain.draw(sandTile);
        }
        else if (tileType == 2)
        {
            grassTile.setPosition(tilePosX, tilePosY);
            terrain.draw(grassTile);
        }
    }
    terrain.display();
    sf::Sprite background;
    background.setTexture(terrain.getTexture());
    return background;
}