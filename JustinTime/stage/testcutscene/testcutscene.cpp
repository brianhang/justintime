#include "testcutscene.h"
#include "../stagedirector.h"
#include "../wakeup/wakeupstage.h"

#include <iostream>

TestCutscene::TestCutscene() : CutsceneStage("scripts/test.txt") {
    std::cout << "Ctor" << std::endl;
}

void TestCutscene::onStart() {
    std::cout << "Started" << std::endl;
}

void TestCutscene::onFinish() {
    std::cout << "Done" << std::endl;
    StageDirector::getInstance().setStage<WakeUpStage>();
}

void TestCutscene::drawBackground(sf::RenderWindow &window) {

}