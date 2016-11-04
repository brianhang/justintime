#include "stage.h"

void Stage::setNextStage(Stage *stage) {
	if (nextStage) {
		delete nextStage;
	}

	nextStage = stage;
}

void Stage::onEvent(const sf::Event &e) {

}