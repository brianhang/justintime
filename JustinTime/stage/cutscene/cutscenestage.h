#pragma once

#include "../stage.h"
#include "cutscenedialog.h"

#include <SFML/Audio.hpp>

class CutsceneStage : public Stage {
    private:
        // A dialog object to see which lines should be displayed.
        CutsceneDialog dialog;

        // Text shape and font for drawing the dialog text.
        sf::Text dialogShape;
        sf::Font dialogFont;

        // A timer for a dialog delay.
        sf::Clock dialogTimer;

        // Cinematic bars at the top and bottom of the screen.
        sf::RectangleShape top;
        sf::RectangleShape bottom;

        // A sprite for drawing an actor's face.
        sf::Sprite actor;

        // Sound for a character being typed.
        sf::SoundBuffer tickSoundBuffer;
        sf::Sound tickSound;

        // Keeps track of which character is being drawn.
        std::string dialogText;
        unsigned int dialogTextIndex;
        
        // States for the text being drawn.
        bool skip;
        bool paused;

    public:
        CutsceneStage();

        void update(float deltaTime);
        void draw(sf::RenderWindow &window);
        void onEvent(const sf::Event &e);

        // Starts a dialog from a given script.
        void load(const std::string &script);

        // Sets the line being typed out to the current line in the dialog.
        void showLine();

        // Called when a dialog starts.
        virtual void onStart() = 0;

        // Called when a dialog contains no more lines, so it is finished.
        virtual void onFinish() = 0;

        // Called when the background of the cutscene needs to be drawn.
        virtual void drawBackground(sf::RenderWindow &window) = 0;
};