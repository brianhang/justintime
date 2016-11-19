#pragma once
#include "../stage.h"

class LectureStage : public Stage {

	public:
		LectureStage();

		void update(float deltaTime);
		void draw(sf::RenderWindow &window);
		void onEvent(const sf::Event &e);
};

