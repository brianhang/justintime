#include "cutscenestage.h"
#include <iostream>\

#define DIALOG_TICK_SOUND "sounds/tick.ogg"
#define DIALOG_FONT "fonts/pressstart2p.ttf"
#define DIALOG_DELAY 0.025f
#define BAR_HEIGHT 96.0f

CutsceneStage::CutsceneStage() {
    // Load the character tick sound.
    if (!tickSoundBuffer.loadFromFile(DIALOG_TICK_SOUND)) {
        std::cerr << "Unable to load dialog tick sound" << std::endl;
    } else {
        tickSound.setBuffer(tickSoundBuffer);
    }

    // Set the dialog text to the dialog font.
    if (!dialogFont.loadFromFile(DIALOG_FONT)) {
        std::cerr << "Unable to load dialog font (" << DIALOG_FONT
                  << std::endl;

        return;
    }

    dialogShape.setFont(dialogFont);
    dialogShape.setCharacterSize(8);

    // Set the appropriate horizontal bar height.
    const sf::Vector2f barSize(640.0f, BAR_HEIGHT);

    top.setSize(barSize);
    bottom.setSize(barSize);

    bottom.setPosition(0.0f, 480.0f - BAR_HEIGHT);

    // Set the color for the bars and the background.
    top.setFillColor(sf::Color::Black);
    bottom.setFillColor(sf::Color::Black);

    background.setSize(sf::Vector2f(640.0f, 480.0f));
    background.setFillColor(sf::Color(125, 125, 125));

    dialogShape.setPosition(96.0f, 480.0f - (BAR_HEIGHT * 0.5f));

    actor.setPosition(0.0f, 480.0f - BAR_HEIGHT);
    actor.setTextureRect(sf::IntRect(0, 0, 96, 96));

    if (dialog.load("scripts/test.txt")) {
        showLine();
    }
}

void CutsceneStage::showLine() {
    CutsceneLine *line = dialog.getLine();

    if (!line) {
        return;
    }

    dialogText = line->actor->name + ": " + line->line;
    dialogTextIndex = 0;

    dialogTimer.restart();
}

void CutsceneStage::update(float deltaTime) {
    if (paused) {
        return;
    }

    if ((skip || dialogTimer.getElapsedTime() >= sf::seconds(DIALOG_DELAY)) &&
        dialogTextIndex <= dialogText.size()) {
        if (dialogTextIndex == 0) {
            CutsceneLine *line = dialog.getLine();

            if (line) {
                actor.setTexture(line->actor->image);
            }
        }

        dialogTextIndex++;

        if (dialogTextIndex > dialogText.size()) {
            dialog.nextLine();

            showLine();
            paused = true;

            return;
        }

        dialogShape.setString(dialogText.substr(0, dialogTextIndex));

        if (dialogText[dialogTextIndex - 1] == '\n') {
            sf::FloatRect bounds = dialogShape.getLocalBounds();

            dialogShape.setOrigin(0.0f, bounds.top + bounds.height * 0.5f);
        }

        if (!skip) {
            tickSound.play();
        }

        dialogTimer.restart();
    }
}

void CutsceneStage::draw(sf::RenderWindow &window) {
    window.draw(background);
    window.draw(top);
    window.draw(bottom);
    window.draw(actor);
    window.draw(dialogShape);
}

void CutsceneStage::onEvent(const sf::Event &e) {
    if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Space) {
        skip = true;
        paused = false;
    } else if (e.type == sf::Event::KeyReleased &&
               e.key.code == sf::Keyboard::Space) {
        skip = false;
    }
}