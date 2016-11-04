#pragma once

#include <SFML/Graphics.hpp>
#include "stage.h"

class StageDirector {
	private:
		// The current stage.
		Stage *stage;

	public:
		StageDirector();
		~StageDirector();

		// Changes the current stage.
		void setStage(Stage *nextStage);

		// Updates the current stage.
		void update(float deltaTime);

		// Called to pass events to the current stage.
		void onEvent(const sf::Event &e);

		// Draws the current stage.
		void draw(sf::RenderWindow &window);

		// Deletes and cleans up the current stage.
		void destroyStage();
};

