#include "EventManager.h"


EventManager* EventManager::sInstance = nullptr;

EventManager::EventManager()
{
	//only allow one EventManager to exist
	assert(sInstance == nullptr);
	sInstance = this;
}

void EventManager::HandleEvents(sf::Window& window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		default:
			break;
		}

		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))

    }
}