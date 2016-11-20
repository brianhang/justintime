#pragma once

#include "../stage.h"
#include "cutscenedialog.h"

#include <SFML/Audio.hpp>

class CutsceneStage : public Stage {
    private:
        CutsceneDialog dialog;

        sf::Text dialogShape;
        sf::Font dialogFont;

        sf::Clock dialogTimer;

        sf::RectangleShape top;
        sf::RectangleShape bottom;
        sf::RectangleShape background;

        sf::Sprite actor;

        sf::SoundBuffer tickSoundBuffer;
        sf::Sound tickSound;

        std::string dialogText;
        unsigned int dialogTextIndex;
        
        bool skip;
        bool paused;

    public:
        CutsceneStage();

        void update(float deltaTime);
        void draw(sf::RenderWindow &window);
        void onEvent(const sf::Event &e);
        void showLine();
};