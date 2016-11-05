#include "stagedirector.h"

StageDirector::StageDirector() {
	stage = nullptr;
}

void StageDirector::setStage(Stage *nextStage) {
	if (stage) {
		destroyStage();
	}

	if (nextStage) {
		stage = nextStage;
	}
}

void StageDirector::draw(sf::RenderWindow &window) {
	if (stage) {
		stage->draw(window);
	}
}

void StageDirector::update(float deltaTime) {
	if (stage) {
		if (stage->nextStage) {
			setStage(stage->nextStage);

			return;
		}

		stage->update(deltaTime);
	}
}

void StageDirector::destroyStage() {
	if (stage) {
		delete stage;
		stage = nullptr;
	}
}

void StageDirector::onEvent(const sf::Event &e) {
	if (stage) {
		stage->onEvent(e);
	}
}

StageDirector::~StageDirector() {
	destroyStage();
}