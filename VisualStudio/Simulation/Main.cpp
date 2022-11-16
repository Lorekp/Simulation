#include <SFML/Graphics.hpp>
#include "AssetManager.h"
#include "TerrainGenerator.h"
#include <vector>

int main()
{
    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Simulation");
    AssetManager manager;
    int mapSizeY = 60;
    int mapSizeX = 60;
    float seed = 324234;

    sf::RenderTexture terrain;
    
    //Terrain generation
    TerrainGenerator generator;
    sf::Sprite background = generator.generateMap(window, mapSizeY, mapSizeX, terrain, seed);



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