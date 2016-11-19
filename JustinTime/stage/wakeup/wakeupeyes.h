#pragma once

#include <SFML/Graphics.hpp>

class WakeUpEyes {
    private:
        sf::RectangleShape top;
        sf::RectangleShape bottom;
        sf::RectangleShape background;
        float sleepiness;
        float tiredness;

    public:
        WakeUpEyes(float newTiredness = 0.0f);

        bool isAwake();
        void setTiredness(float newTiredness);
        void wakeUp(float amount);
        void update(float deltaTime);
        void draw(sf::RenderWindow &window);
};