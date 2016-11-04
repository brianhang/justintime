#pragma once

#include <SFML/Graphics.hpp>
#include "stage.h"

class Stage1 : public Stage {
	private:
		sf::Text text;
		sf::Font font;
		float time;

	public:
		Stage1();
		~Stage1();
		void update(float deltaTime);
		void onEvent(const sf::Event &e);
		void draw(sf::RenderWindow &window);
};

