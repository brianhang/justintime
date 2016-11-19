#include "wakeupeyes.h"
#include <iostream>

WakeUpEyes::WakeUpEyes(float newTiredness) {
    const sf::Vector2f eyeSize(640.0f, 239.0f);

    // Set the background to fill the screen.
    background.setSize(sf::Vector2f(640.0f, 480.0f));
    background.setFillColor(sf::Color::White);

    // Set the eyelids to fill up half the screen each.
    top.setSize(eyeSize);
    top.setFillColor(sf::Color::Black);

    bottom.setSize(eyeSize);
    bottom.setFillColor(sf::Color::Black);

    // Set the eyes to a closed position.
    sleepiness = 1.0f;
    tiredness = newTiredness;

    // Place the eyelids in the correct position on the screen.
    bottom.setPosition(0.0f, 481.0f);
    bottom.setOrigin(0.0f, 240.0f);
}

bool WakeUpEyes::isAwake() {
    return sleepiness <= 0.0f;
}

void WakeUpEyes::wakeUp(float amount) {
    sleepiness -= amount;
}

void WakeUpEyes::setTiredness(float newTiredness) {
    tiredness = newTiredness;
}

void WakeUpEyes::update(float deltaTime) {
    // Keep closing the eyes if nothing is done.
    if (sleepiness < 1.0f) {
        sleepiness = std::min(sleepiness + tiredness, 1.0f);
    }

    // Adjust the eyelid scale to make them appear more open.
    top.setScale(sf::Vector2f(1.0f, sleepiness));
    bottom.setScale(sf::Vector2f(1.0f, sleepiness));
}

void WakeUpEyes::draw(sf::RenderWindow &window) {
    window.draw(background);
    window.draw(top);
    window.draw(bottom);
}