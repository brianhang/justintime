#include "cutscenestage.h"
#include <iostream>\

#define DIALOG_TICK_SOUND "sounds/tick.ogg"
#define DIALOG_FONT "fonts/pressstart2p.ttf"
#define DIALOG_DELAY 0.05f
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

    dialog.setFont(dialogFont);
    dialog.setCharacterSize(8);

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

    setText("Lorem Ipsum is simply dummy text of the printing\n" \
            "andtypesetting industry. Lorem Ipsum has been\n" \
            "the industry's standard dummy text ever since the\n" \
            "1500s, when an unknown printer took a galley of\n" \
            "type and scrambled it to make a type\n" \
            "specimen book.");
}

void CutsceneStage::setText(const std::string &text) {
    dialogText = text;
    dialogTextIndex = 0;

    dialogTimer.restart();

    dialog.setString("");
    dialog.setPosition(48.0f, 480.0f - (BAR_HEIGHT * 0.5f));
}

void CutsceneStage::update(float deltaTime) {
    if ((skip || dialogTimer.getElapsedTime() >= sf::seconds(DIALOG_DELAY)) &&
        dialogTextIndex < dialogText.size()) {
        dialogTextIndex++;
        dialog.setString(dialogText.substr(0, dialogTextIndex));

        if (dialogTextIndex == 0 || dialogText[dialogTextIndex - 1] == '\n') {
            sf::FloatRect bounds = dialog.getLocalBounds();

            dialog.setOrigin(0.0f, bounds.top + bounds.height * 0.5f);
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
    window.draw(dialog);
}

void CutsceneStage::onEvent(const sf::Event &e) {
    if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Space) {
        skip = true;
    } else if (e.type == sf::Event::KeyReleased &&
               e.key.code == sf::Keyboard::Space) {
        skip = false;
    }
}