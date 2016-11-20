#pragma once

#include "../stage.h"
#include <SFML/Audio.hpp>

class CutsceneStage : public Stage {
    private:
        sf::Text dialog;
        sf::Font dialogFont;

        sf::Clock dialogTimer;

        sf::RectangleShape top;
        sf::RectangleShape bottom;
        sf::RectangleShape background;

        sf::SoundBuffer tickSoundBuffer;
        sf::Sound tickSound;

        std::string dialogText;
        unsigned int dialogTextIndex;
        
        bool skip;

    public:
        CutsceneStage();

        void update(float deltaTime);
        void draw(sf::RenderWindow &window);
        void onEvent(const sf::Event &e);
        void setText(const std::string &text);
};