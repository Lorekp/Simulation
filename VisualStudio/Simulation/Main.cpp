#include <SFML/Graphics.hpp>
#include "AssetManager.h"
#include "TerrainGenerator.h"
#include "EventManager.h"
#include <vector>

int main()
{
    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Simulation");
    AssetManager manager;
    EventManager handler;

    int mapSizeY = 60;
    int mapSizeX = 60;
    int seed = 11022006;

    sf::RenderTexture terrain;
    terrain.create(window.getSize().y, window.getSize().x);
    terrain.clear();
    
    //Terrain generation
    TerrainGenerator generator;
    sf::Sprite background = generator.generateMap(mapSizeY, mapSizeX, terrain, seed);
    background.setPosition((static_cast<float>(window.getSize().x) - mapSizeX * 16) / 2, (static_cast<float>(window.getSize().y) - mapSizeY * 16) / 2);

//Game Loop
    while (window.isOpen())
    {
        handler.HandleEvents(window);

        window.clear();
        window.draw(background);
        window.display();
    }

    return 0;
}