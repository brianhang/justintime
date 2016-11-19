#include "wakeupeyes.h"
#include <iostream>

WakeUpEyes::WakeUpEyes(float newTiredness) {
    const sf::Vector2f eyeSize(640.0f, 238.0f);

    background.setSize(sf::Vector2f(640.0f, 480.0f));
    background.setFillColor(sf::Color::White);

    top.setSize(eyeSize);
    top.setFillColor(sf::Color::Black);

    bottom.setSize(eyeSize);
    bottom.setFillColor(sf::Color::Black);

    sleepiness = 1.0f;
    tiredness = newTiredness;

    bottom.setPosition(0.0f, 480.0f);
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
    if (sleepiness < 1.0f) {
        sleepiness = std::min(sleepiness + tiredness, 1.0f);
    }

    float scale = sleepiness / 1.0f;
    std::cout << scale << std::endl;
    top.setScale(sf::Vector2f(1.0f, scale));
    bottom.setScale(sf::Vector2f(1.0f, scale));
}

void WakeUpEyes::draw(sf::RenderWindow &window) {
    window.draw(background);
    window.draw(top);
    window.draw(bottom);
}