#include "stagedirector.h"

StageDirector &StageDirector::getInstance() {
    static StageDirector instance;

    return instance;
}

void StageDirector::draw(sf::RenderWindow &window) {
    // Delegate drawing to the current stage.
    if (stage.get()) {
        stage->draw(window);
    }
}

void StageDirector::update(float deltaTime) {
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

Stage *StageDirector::getStage() {
    return stage.get();
}