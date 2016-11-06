#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "stage.h"

class StageDirector {
	private:
		// The current stage.
        std::unique_ptr<Stage> stage;

	public:
		StageDirector();

		// Changes the current stage.
		void setStage(Stage *newStage);

		// Updates the current stage.
		void update(float deltaTime);

		// Called to pass events to the current stage.
		void onEvent(const sf::Event &e);

		// Draws the current stage.
		void draw(sf::RenderWindow &window);
};

