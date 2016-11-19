#include "justintime.h"
#include <stdlib.h>

JustinTime::JustinTime() : director(StageDirector::getInstance()) {
    // Set the random seed to the current time to randomize values.
    srand((unsigned int)time(NULL));
}

void JustinTime::run(const std::string &title, int width, int height) {
    // Create a window for the game.
    window.create(sf::VideoMode(width, height), title);
    window.setFramerateLimit(60);

    // Stage director to handle stages within a game.
    director.setStage<MenuStage>();

    // Game loop.
    while (window.isOpen()) {
        handleInput();
        update();
        draw();
    }
}

void JustinTime::handleInput() {
    sf::Event e;

    // Delegate each event to the stage.
    while (window.pollEvent(e)) {
        if (e.type == sf::Event::Closed) {
            window.close();
        }

        director.onEvent(e);
    }
}

void JustinTime::update() {
    // Calculate the time from the last frame.
    float deltaTime = deltaClock.getElapsedTime().asSeconds();
    deltaClock.restart();

    // Update the stage.
    director.update(deltaTime);
}

void JustinTime::draw() {
    // Clear the window to draw the next frame.
    window.clear();

    // Draw the next frame.
    director.draw(window);
    window.display();
}