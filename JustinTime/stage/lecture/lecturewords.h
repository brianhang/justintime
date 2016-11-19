#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class LectureWords {
	private:
        sf::RectangleShape container;
        bool isTyped;

	public:
        LectureWords(std::string word);

		void update(float deltaTime);
		void draw(sf::RenderWindow &window);
};