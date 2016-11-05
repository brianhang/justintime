#pragma once

#include <SFML/Graphics.hpp>

#include "lua/lua.hpp"

class DrawContext {
    private:
        // A generic rectangle to draw rectangular shapes.
        sf::RectangleShape rectangleShape;

        // A generic polygon to draw polygon shapes.
        sf::CircleShape polygonShape;

        // RenderWindow for drawing shapes.
        sf::RenderWindow *window;

    public:
        // Empty constructor.
        DrawContext();

        // Returns the singleton instance.
        static DrawContext &getInstance();

        // Sets which window the DrawContext affects.
        void setWindow(sf::RenderWindow *newWindow);

        // Sets which color will be used for drawing shapes.
        static int setColor(lua_State *lua);

        // Sets which color will be used for outlining shapes.
        static int setOutlineColor(lua_State *lua);

        // Sets the thickness of shape outlines.
        static int setOutlineThickness(lua_State *lua);

        // Sets the rotation of shapes being drawn in degrees.
        static int setRotation(lua_State *lua);

        // Draws a rectangle at (x, y) with a given width and height.
        static int rectangle(lua_State *lua);

        // Draws a polygon with a given width and height.
        static int polygon(lua_State *lua);

        // Draws a line from (x1, y1) to (x2, y2).
        static int line(lua_State *lua);

        // Sets up Lua bindings for drawing shapes using a DrawingContext.
        void bind(lua_State *lua);
};