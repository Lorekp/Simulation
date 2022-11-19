#ifndef TERRAIN_GENERATOR_H
#define TERRAIN_GENERATOR_H

#include <vector>
#include <SFML/Graphics.hpp>

class TerrainGenerator {

public:
	TerrainGenerator();

	sf::Sprite generateMap(int width, int height, sf::RenderTexture& terrain, int seed);

	std::vector<int> generateNoiseMap(int seed, int width, int height);
private:
	static TerrainGenerator* sInstance;
	
};

#endif