#pragma once

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

#include "actor.h"

/*
 * The StageCast class manages actors (objects on the stage) by controlling the
 * creation, deletion, and lifetime of actors. This should be responsible for
 * containing all actors that are needed and allow actors to be retrieved to
 * do certain actions. This allows the lifetime of the actors to be independent
 * from the main program.
 */
class StageCast {
    private:
        std::vector<std::unique_ptr<Actor>> actors;

    public:
        StageCast();
        ~StageCast();

        template<typename T>
        T *create();

        void update(float deltaTime);
        void draw(sf::RenderWindow &window);
        void clean();
};