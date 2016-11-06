#include "stagedirector.h"

StageDirector &StageDirector::getInstance() {
    static StageDirector instance;

    return instance;
}

void StageDirector::setStage(Stage *newStage) {
    // Change what the next stage is.
    nextStage.reset(newStage);
}

void StageDirector::draw(sf::RenderWindow &window) {
    // Delegate drawing to the current stage.
	if (stage.get()) {
		stage->draw(window);
	}
}

bool StageDirector::isChangingStage() {
    return nextStage.get() != nullptr;
}

void StageDirector::update(float deltaTime) {
    if (nextStage.get()) {
        // A stage change is requested, so notify the current stage.
        if (stage.get()) {
            stage->onLeave();
        }

        // Set the current stage to be the next stage.
        stage = std::move(nextStage);

        return;
    }

    // Update the current stage.
	if (stage.get()) {
        stage->update(deltaTime);
	}
}

void StageDirector::onEvent(const sf::Event &e) {
    // Delegate event handling to the current stage.
	if (stage.get()) {
		stage->onEvent(e);
	}
}