#pragma once

#include "stage.h"
#include "drawcontext.h"
#include "lua/lua.hpp"

#include <memory>

class LuaStage : public Stage {
    private:
        std::string nextStage;

        lua_State *lua;

        // Lua function to change the current stage.
        static int setNextStage(lua_State *lua);

        // Sets up the Stage API for Lua scripts.
        void setupLuaStage();

        // Prints the last Lua error.
        void printError();

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

        // Called when the stage is being changed to another.
        void onLeave();
};