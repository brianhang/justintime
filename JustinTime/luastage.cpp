#include <iostream>

#include "luastage.h"

static void stackDump(lua_State *L) {
    int i;
    int top = lua_gettop(L);
    for (i = 1; i <= top; i++) {  /* repeat for each level */
        int t = lua_type(L, i);
        switch (t) {

        case LUA_TSTRING:  /* strings */
            printf("`%s'", lua_tostring(L, i));
            break;

        case LUA_TBOOLEAN:  /* booleans */
            printf(lua_toboolean(L, i) ? "true" : "false");
            break;

        case LUA_TNUMBER:  /* numbers */
            printf("%g", lua_tonumber(L, i));
            break;

        default:  /* other values */
            printf("%s", lua_typename(L, t));
            break;

        }
        printf("  ");  /* put a separator */
    }
    printf("\n");  /* end the listing */
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
}

LuaStage::~LuaStage() {
    if (lua) {
        lua_close(lua);
    }
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