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
    window.setFramerateLimit(60);

	// Stage director to handle stages within a game.
    StageDirector &director = StageDirector::getInstance();
    director.setStage<MenuStage>();

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

        // Update and draw the current state of the game.
		director.update(deltaTime);
		director.draw(window);

        window.display();
    }

    return 0;
}