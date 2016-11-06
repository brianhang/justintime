#include <iostream>

#include "stagedirector.h"
#include "luastage.h"

#if _DEBUG
#include "debug_stackdump.h"
#endif

static int emptyLuaFunction(lua_State *lua) {
    return 0;
}

LuaStage::LuaStage(const std::string &fileName) :
lua(nullptr) {
    // Create the Lua state to run Lua scripts with.
    lua = luaL_newstate();

    if (!lua) {
        std::cerr << "Unable to open new Lua state!" << std::endl;

        return;
    }

    // Open up the standard library for use.
    luaL_openlibs(lua);

    // Open the Lua script for the stage.

    // Create variables needed for the stage.
    setupLuaStage();

    // Set up drawing functions.
    DrawContext::getInstance().bind(lua);

    if (luaL_loadfile(lua, fileName.c_str())) {
        printError();

        return;
    }

    if (lua_pcall(lua, 0, 0, 0)) {
        printError();

        return;
    }

    // Call the stage's initialize function.
    lua_getglobal(lua, "stage");

    if (!lua_istable(lua, -1)) {
        std::cerr << "[" << fileName << "] 'stage' is not a table!"
                  << std::endl;

        return;
    }

    // Get the initialize function.
    lua_pushstring(lua, "init");
    lua_gettable(lua, -2);

    // Call the initialize function.
    if (lua_isfunction(lua, -1)) {
        lua_getglobal(lua, "stage");
        lua_call(lua, 1, 0);
    }

    lua_pop(lua, 2);
}

void LuaStage::setupLuaStage() {
    lua_newtable(lua);
    lua_setglobal(lua, "stage");

    // Add the stage:setNextStage(nextStage) function.
    lua_getglobal(lua, "stage");
    lua_pushcfunction(lua, LuaStage::setNextStage);
    lua_setfield(lua, -2, "setNextStage");
}

LuaStage::~LuaStage() {
    if (lua) {
        lua_close(lua);
    }
}

int LuaStage::setNextStage(lua_State *lua) {
    // Make sure a "self" was specified.
    luaL_checktype(lua, 1, LUA_TTABLE);

    // Call the stage:exit() function.
    lua_pushstring(lua, "exit");
    lua_gettable(lua, -3);

    if (lua_isfunction(lua, -1)) {
        lua_getglobal(lua, "stage");
        lua_call(lua, 1, 0);
    } else {
        lua_pop(lua, 1);
    }

    // Get the Lua script for the next stage.
    std::string nextStage(luaL_checkstring(lua, 2));
    nextStage = "stages/" + nextStage + ".lua";

    // Do not allow future stage changes.
    lua_getglobal(lua, "stage");
    lua_pushcfunction(lua, emptyLuaFunction);
    lua_setfield(lua, -2, "setNextStage");

    // Switch the stage.
    StageDirector::getInstance().setStage(new LuaStage(nextStage));

    return 0;
}

void LuaStage::printError() {
    if (lua) {
        // Output the top string (the error) to stderr.
        std::cerr << lua_tostring(lua, -1) << std::endl;
        lua_pop(lua, 1);
    }
}

void LuaStage::draw(sf::RenderWindow &window) {
    // Get the stage table.
    lua_getglobal(lua, "stage");

    if (!lua_istable(lua, -1)) {
        lua_pop(lua, 1);

        return;
    }

    // Get the update function.
    lua_pushstring(lua, "draw");
    lua_gettable(lua, -2);

    // Call the update function.
    if (lua_isfunction(lua, -1)) {
        lua_getglobal(lua, "stage");

        if (lua_pcall(lua, 1, 0, 0)) {
            printError();
        }

        lua_pop(lua, 1);
    }
    else {
        lua_pop(lua, 2);
    }
}                       

void LuaStage::update(float deltaTime) {
    // Get the stage table.
    lua_getglobal(lua, "stage");

    if (!lua_istable(lua, -1)) {
        lua_pop(lua, 1);

        return;
    }

    // Get the update function.
    lua_pushstring(lua, "update");
    lua_gettable(lua, -2);

    // Call the update function.
    if (lua_isfunction(lua, -1)) {
        lua_getglobal(lua, "stage");
        lua_pushnumber(lua, deltaTime);
        
        if (lua_pcall(lua, 2, 0, 0)) {
            printError();
        }

        lua_pop(lua, 1);
    }
    else {
        lua_pop(lua, 2);
    }
}

void LuaStage::onEvent(const sf::Event &e) {

}

void LuaStage::onLeave() {

}