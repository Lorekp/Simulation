#ifndef TERRAIN_GENERATOR_H
#define TERRAIN_GENERATOR_H

class TerrainGenerator {

public:
	TerrainGenerator();

	std::vector<sf::Texture> generateMap(int seed, int width, int height);

private:
	static TerrainGenerator* sInstance;
	
};

#endif