#pragma once

#include "stage.h"
#include "drawcontext.h"
#include "lua/lua.hpp"

class LuaStage : public Stage {
    private:
        lua_State *lua;

    public:
        // LuaStage constructor.
        LuaStage(const std::string &fileName);

        // LuaStage destructor.
        ~LuaStage();

        // Renders the stage to the window.
        void draw(sf::RenderWindow &window);

        // Handles the logic for the stage.
        void update(float deltaTime);

        // Handles events for the game.
        void onEvent(const sf::Event &e);

        // Prints the last Lua error.
        void printError();

        // Sets up the Stage API for Lua scripts.
        void setupLuaStage();
};