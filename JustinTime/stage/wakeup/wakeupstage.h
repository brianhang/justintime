#pragma once

#include "../stage.h"
#include "wakeupeyes.h"

class WakeUpStage : public Stage {
    private:
        WakeUpEyes eyes;

    public:
        WakeUpStage();

        void update(float deltaTime);
        void draw(sf::RenderWindow &window);
        void onEvent(const sf::Event &e);
};

