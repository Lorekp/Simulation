#include <SFML/Graphics.hpp>
#include "AssetManager.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Simulation");
    AssetManager manager;

    //Background setup
    sf::Texture texture = sf::Texture(AssetManager::GetTexture("PNGs/tile256.png"));
    texture.setRepeated(true);

    sf::RectangleShape background(sf::Vector2f(256 * 5, 256 * 5));
    background.setTextureRect(sf::IntRect(0, 0, 256 * 5, 256 * 5));
    background.setTexture(&texture);
    background.setPosition((window.getSize().x - (256 * 5)) / 2, (window.getSize().y - (256 * 5)) / 2);

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