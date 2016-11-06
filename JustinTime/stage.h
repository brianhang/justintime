#pragma once

#include <SFML/Graphics.hpp>

class Stage {
	public:
		virtual ~Stage() { };

		// Called to update the stage each frame.
		virtual void update(float deltaTime) = 0;

		// Called to draw the stage for the frame.
		virtual void draw(sf::RenderWindow &window) = 0;

		// Called when an event was received.
		virtual void onEvent(const sf::Event &e) = 0;
};