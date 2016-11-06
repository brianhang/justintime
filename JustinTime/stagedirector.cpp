#include "stagedirector.h"

StageDirector::StageDirector() {
    stage.reset();
}

void StageDirector::setStage(Stage *newStage) {
    stage.reset(newStage);
}

void StageDirector::draw(sf::RenderWindow &window) {
	if (stage.get()) {
		stage->draw(window);
	}
}

void StageDirector::update(float deltaTime) {
	if (stage.get()) {
        /*
		if (stage->nextStage) {
			setStage(stage->nextStage);

			return;
		}
        */

		stage->update(deltaTime);
	}
}

void StageDirector::onEvent(const sf::Event &e) {
	if (stage.get()) {
		stage->onEvent(e);
	}
}