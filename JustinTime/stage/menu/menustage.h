#pragma once

#include "../stage.h"
#include <vector>

class MenuStage : public Stage {
    private:
        sf::Texture face;
        sf::Sprite centerFace;
        sf::RectangleShape fade;
        sf::Text title;
        sf::Font font;

        float time;

    public:
        MenuStage();
        void draw(sf::RenderWindow &window);
        void update(float deltaTime);
        void onEvent(const sf::Event &e);
};