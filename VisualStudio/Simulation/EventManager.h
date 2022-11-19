#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <assert.h>
#include <SFML/Graphics.hpp>

class EventManager {

public:
	EventManager();

	void HandleEvents(sf::Window& window);

private:
	static EventManager* sInstance;

};

#endif 
