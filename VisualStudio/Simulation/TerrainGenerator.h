#ifndef TERRAIN_GENERATOR_H
#define TERRAIN_GENERATOR_H

class TerrainGenerator {

public:
	TerrainGenerator();

	

private:
	static TerrainGenerator* sInstance;
	double generateMap(int seed, int width, int height);
};

#endif