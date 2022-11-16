#include <SFML/Graphics.hpp>
#include "AssetManager.h"
#include "TerrainGenerator.h"
#include <vector>

int main()
{
    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Simulation");
    AssetManager manager;
    int mapSizeY = 50;
    int mapSizeX = 50;

    //setup tiles
    sf::Sprite waterTile;
    sf::Sprite sandTile;
    sf::Sprite grassTile;
    const int tileTypeAmount = 3;
    waterTile.setTexture(AssetManager::GetTexture("Textures/Environment/water1.png"));
    sandTile.setTexture(AssetManager::GetTexture("Textures/Environment/sandClear.png"));
    grassTile.setTexture(AssetManager::GetTexture("Textures/Environment/grassClear.png"));
    sf::Sprite tileTypes[tileTypeAmount] = {waterTile, sandTile, grassTile};
    
    //Terrain generation
    TerrainGenerator generator;
    sf::Sprite background = generator.generateMap(window, 50, 50, tileTypes);

    //Game Loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(background);
        window.display();
    }

    return 0;
}