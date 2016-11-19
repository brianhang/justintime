#pragma once

#include "stagedirector.h"

#include <SFML/Graphics.hpp>

class JustinTime {
    // Clock for time between frames.
    sf::Clock deltaClock;

    // The window for the game.
    sf::RenderWindow window;

    // Handles the game state.
    StageDirector &director;

    private:
        // Handles the user input for the game.
        void handleInput();

        // Draws the current state of the game.
        void draw();
        
        // Handles the game logic.
        void update();

    public:
        // Constructor for the JustinTime game.
        JustinTime();

        // Starts the game loop.
        void run(const std::string &title, int width, int height);
};