#include "drawcontext.h"

sf::RenderWindow *DrawContext::window = nullptr;
sf::RectangleShape DrawContext::rectangleShape;

DrawContext::DrawContext() { }

DrawContext &DrawContext::getInstance() {
    static DrawContext drawContext;

    return drawContext;
}

void DrawContext::setWindow(sf::RenderWindow *newWindow) {
    DrawContext::window = newWindow;
}

int DrawContext::setColor(lua_State *lua) {
    DrawContext drawContext = DrawContext::getInstance();

    // Get the RGB parameters.
    unsigned char red = (unsigned char) luaL_checknumber(lua, 1);
    unsigned char green = (unsigned char) luaL_checknumber(lua, 2);
    unsigned char blue = (unsigned char) luaL_checknumber(lua, 3);
    unsigned char alpha = 255;

    // Get the optional alpha parameter.
    if (lua_gettop(lua) > 3) {
        alpha = (unsigned char) lua_tointeger(lua, -4);
    }

    // Create a color object with the RGBA values.
    sf::Color color(red, green, blue, alpha);

    // Set the shape color to be the given color.
    DrawContext::rectangleShape.setFillColor(color);
    drawContext.polygonShape.setFillColor(color);

    return 0;
}

int DrawContext::setOutlineColor(lua_State *lua) {
    return 0;
}

int DrawContext::setOutlineThickness(lua_State *lua) {
    return 0;
}

int DrawContext::setRotation(lua_State *lua) {
    return 0;
}

int DrawContext::rectangle(lua_State *lua) {
    DrawContext drawContext = DrawContext::getInstance();

    if (!DrawContext::window) {
        return 0;
    }

    float x = (float) luaL_checknumber(lua, 1);
    float y = (float) luaL_checknumber(lua, 2);
    float width = (float) luaL_checknumber(lua, 3);
    float height = (float) luaL_checknumber(lua, 4);

    DrawContext::rectangleShape.setPosition(x, y);
    DrawContext::rectangleShape.setSize(sf::Vector2f(width, height));

    DrawContext::window->draw(DrawContext::rectangleShape);

    return 0;
}

int DrawContext::polygon(lua_State *lua) {
    return 0;
}

int DrawContext::line(lua_State *lua) {
    return 0;
}

// Set up a library mapping from C++ to Lua.
static const luaL_Reg draw[] = {
    {"setColor", DrawContext::setColor},
    {"rectangle", DrawContext::rectangle},
    {NULL, NULL} // Sentinel
};

void DrawContext::bind(lua_State *lua) {
    luaL_newlib(lua, draw);
    lua_setglobal(lua, "draw");
}