#pragma once

#include "../cutscene/cutscenestage.h"

class TestCutscene : public CutsceneStage {
    public:
        TestCutscene();

        virtual void onStart();
        void onFinish();
        void drawBackground(sf::RenderWindow &window);
};