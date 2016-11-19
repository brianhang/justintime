#include "wakeupstage.h"
#include "../stagedirector.h"
#include "../menu/menustage.h"

WakeUpStage::WakeUpStage() : eyes(0.01f) { }

void WakeUpStage::update(float deltaTime) {
    eyes.update(deltaTime);
}

void WakeUpStage::draw(sf::RenderWindow &window) {
    eyes.draw(window);
}

void WakeUpStage::onEvent(const sf::Event &e) {
    // Open the eyes more every time a mouse button is pressed.
    if (e.type == sf::Event::MouseButtonPressed) {
        eyes.wakeUp(0.1f);

        // If the eyes are fully open, go to another stage.
        if (eyes.isAwake()) {
            StageDirector::getInstance().setStage<MenuStage>();
        }
    }
}