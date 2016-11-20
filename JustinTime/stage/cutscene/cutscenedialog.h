#pragma once

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

// An actor within a dialog. Actors simply have a name and identifying image.
typedef struct {
    std::string name;
    sf::Texture image;
} CutsceneActor;

// A line within a dialog that is associated with an actor.
typedef struct {
    std::shared_ptr<CutsceneActor> actor;
    std::string line;
} CutsceneLine;

class CutsceneDialog {
    private:
        // A list of actors for the dialog.
        std::vector<std::shared_ptr<CutsceneActor>> actors;
        
        // A list of lines in the dialog.
        std::vector<std::unique_ptr<CutsceneLine>> lines;

        // Which line the dialog is current at.
        unsigned int line;

    public:
        // Parses a dialog script so it can be used.
        bool load(const std::string &script);

        // Moves to the next line in the dialog and returns it.
        CutsceneLine *nextLine();

        // Returns the current line of the dialog.
        CutsceneLine *getLine();

        // Restarts the dialog from the first line.
        void reset();
};