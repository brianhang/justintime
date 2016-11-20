#include "cutscenedialog.h"
#include <string>
#include <iostream>
#include <fstream>
#include <regex>

bool CutsceneDialog::load(const std::string &script) {
    // Open the script file to read.
    std::ifstream stream(script);
    
    // Load each line of the script.
    for (std::string scriptLine; std::getline(stream, scriptLine);) {
        switch (scriptLine[0]) {
            // Lines that start with # are comments.
            case '#':
                break;
            // Lines that start with @ define an actor.
            case '@': {
                // Find the actor definition in the line.
                const std::regex re("@(\\d+);([^;]+);(.+)");
                std::smatch match;

                // Add the actor if found.
                if (std::regex_search(scriptLine, match, re) &&
                    match.size() > 1) {
                    CutsceneActor *actor = new CutsceneActor();
                    actor->name = match[2];
                    actor->image = match[3];

                    int index = std::stoi(match[1]) - 1;

                    actors.insert(actors.begin() + index,
                                  std::unique_ptr<CutsceneActor>(actor));
                } else {
                    // If there was a malformed definition, report the error
                    // and indicate it by returning false.
                    std::cerr << "CutsceneDialog::load(" << script << ") - "
                              << "Invalid actor definition ("
                              << scriptLine << ")";

                    return false;
                }

                break;
            }
            // Otherwise, the line is a dialog line.
            default: {
                // Find the actor and the text.
                const std::regex re("(\\d+)[\\s](.+)");
                std::smatch match;

                // Add the line with the given actor and text if found.
                if (std::regex_search(scriptLine, match, re) &&
                    match.size() > 1) {
                    // Find which actor is suppose to speak.
                    int actor = std::stoi(match[1]) - 1;

                    // Error if the desired actor does not exist.
                    if (actors.size() <= actor) {
                        std::cerr << "CutsceneDialog::load(" << script << ") - "
                            << "Invalid actor " << actor << " ("
                            << scriptLine << ")";

                        return false;
                    }

                    CutsceneLine *line = new CutsceneLine();
                    line->actor = actors[actor];
                    line->line = match[2];

                    lines.push_back(std::unique_ptr<CutsceneLine>(line));
                } else {
                    // Ignore empty lines.
                    const std::regex empty("(^[\\s])");
                    
                    if (!std::regex_search(scriptLine, match, empty)) {
                        continue;
                    }

                    // If there was a malformed line, report the error
                    // and indicate it by returning false.
                    std::cerr << "CutsceneDialog::load(" << script << ") - "
                        << "Invalid actor line ("
                        << scriptLine << ")";

                    return false;
                }

                break;
            }
        }
    }

    return true;
}

CutsceneLine *CutsceneDialog::nextLine() {
    line++;

    if (line >= lines.size()) {
        return nullptr;
    }

    return lines[line].get();
}

CutsceneLine *CutsceneDialog::getLine() {
    return lines[line].get();
}

void CutsceneDialog::reset() {
    line = 0;
}