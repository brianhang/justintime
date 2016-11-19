#pragma once

#include <SFML/Graphics.hpp>

/*
 * Actors are objects within a stage. They have their own states and are
 * responsible for updating their own states and drawing themselves on the
 * stage when needed.
 */
class Actor {
    private:
        bool dying = true;

    public:
        virtual void init() = 0;
        virtual void update(float deltaTime) = 0;
        virtual void draw(sf::RenderWindow &window) = 0;
        void remove();
        bool isDying();
        virtual ~Actor();
};