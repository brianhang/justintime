#pragma once

#include <vector>
#include <memory>

// An actor within a dialog. Actors simply have a name and identifying image.
typedef struct {
    std::string name;
    std::string image;
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
        int line;

    public:
        // Constructor that parses a dialog script.
        CutsceneDialog(const std::string &script);

        // Moves to the next line in the dialog and returns it.
        CutsceneLine *nextLine();

        // Returns the current line of the dialog.
        CutsceneLine *getLine();

        // Restarts the dialog from the first line.
        void reset();
};