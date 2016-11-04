#include "stagedirector.h"
#include "menustage.h"

#include <SFML/Graphics.hpp>
#include <iostream>


int main() {
	srand((unsigned int) time(NULL));

	// Clock to keep track of time between frames.
	sf::Clock deltaClock;

	// Create a window for the game.
    sf::RenderWindow window(sf::VideoMode(640, 480), "SFML Test");

	// Stage director to handle stages within a game.
	StageDirector director;
	director.setStage(new MenuStage());

	// Game loop.
    while (window.isOpen()) {
		// Calculate the time from the last frame.
		float deltaTime = deltaClock.getElapsedTime().asSeconds();
		deltaClock.restart();

		// Handle game input.
        sf::Event e;

        while (window.pollEvent(e)) {
			if (e.type == sf::Event::Closed) {
				window.close();
			}

			director.onEvent(e);
        }

		// Update and draw the current state.
        window.clear();
		
		director.update(deltaTime);
		director.draw(window);

        window.display();
    }

    return 0;
}