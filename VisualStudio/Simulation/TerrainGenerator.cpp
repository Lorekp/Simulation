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

	gen.SetFrequency(0.01f);
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

sf::Sprite TerrainGenerator::generateMap(sf::RenderWindow& window, int width, int height, sf::Sprite tileTypes[])
{
    //Background setup
    sf::RenderTexture terrain;
    terrain.create(window.getSize().y, window.getSize().x);
    terrain.clear();

    std::vector<int> genMap = TerrainGenerator::generateNoiseMap(1, width, height);
    //make a background texture out of the single tiles
    int tilePosX = 0;
    int tilePosY = 0;
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
            tileTypes[0].setPosition(tilePosX, tilePosY);
            terrain.draw(tileTypes[0]);
        }
        else if (tileType == 1)
        {
            tileTypes[1].setPosition(tilePosX, tilePosY);
            terrain.draw(tileTypes[1]);
        }
        else if (tileType == 2)
        {
            tileTypes[2].setPosition(tilePosX, tilePosY);
            terrain.draw(tileTypes[2]);
        }
    }
    terrain.display();
    sf::Sprite background;
    background.setTexture(terrain.getTexture());
    return background;
}