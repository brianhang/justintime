#include <cmath>
#include <iostream>
#include "drawcontext.h"

#define RAD2DEG (180.0f / 3.14159265f)

DrawContext::DrawContext() { }

DrawContext &DrawContext::getInstance() {
    static DrawContext drawContext;

    return drawContext;
}

void DrawContext::setWindow(sf::RenderWindow *newWindow) {
    window = newWindow;
}

/*
 * Lua Function: draw.setColor(red, green, blue, alpha)
 * Description:  Sets the color for shapes being drawn.
 * Parameters:   red - how much red there is (0-255)
 *               green - how much green there is (0-255)
 *               blue - how much blue there is (0-255)
 *               alpha - the transparency (0-255), default is 255
 * Returns:      None.
 */
int DrawContext::setColor(lua_State *lua) {
    DrawContext &drawContext = DrawContext::getInstance();

    // Get the RGB parameters.
    unsigned char red = (unsigned char) luaL_checknumber(lua, 1);
    unsigned char green = (unsigned char) luaL_checknumber(lua, 2);
    unsigned char blue = (unsigned char) luaL_checknumber(lua, 3);
    unsigned char alpha = 255;

    // Get the optional alpha parameter.
    if (lua_gettop(lua) > 3) {
        alpha = (unsigned char)luaL_checknumber(lua, 4);
    }

    // Create a color object with the RGBA values.
    sf::Color color(red, green, blue, alpha);

    // Set the shape color to be the given color.
    drawContext.rectangleShape.setFillColor(color);
    drawContext.polygonShape.setFillColor(color);

    return 0;
}

/*
 * Lua Function: draw.setOutlineColor(red, green, blue, alpha)
 * Description:  
 * Parameters:   red - how much red there is (0-255)
 *               green - how much green there is (0-255)
 *               blue - how much blue there is (0-255)
 *               alpha - the transparency (0-255), default is 255
 * Returns:      None.
 */
int DrawContext::setOutlineColor(lua_State *lua) {
    DrawContext &drawContext = DrawContext::getInstance();

    // Get the RGB parameters.
    unsigned char red = (unsigned char)luaL_checknumber(lua, 1);
    unsigned char green = (unsigned char)luaL_checknumber(lua, 2);
    unsigned char blue = (unsigned char)luaL_checknumber(lua, 3);
    unsigned char alpha = 255;

    // Get the optional alpha parameter.
    if (lua_gettop(lua) > 3) {
        alpha = (unsigned char) luaL_checknumber(lua, 4);
    }

    // Create a color object with the RGBA values.
    sf::Color color(red, green, blue, alpha);

    // Set the shape color to be the given color.
    drawContext.rectangleShape.setOutlineColor(color);
    drawContext.polygonShape.setOutlineColor(color);

    return 0;
}

/*
 * Lua Function: draw.setOutlineThickness(thickness)
 * Description:  Sets how much outlines should be drawn for shapes.
 * Parameters:   thickness - the thickness of the outline in pixels
 * Returns:      None.
 */
int DrawContext::setOutlineThickness(lua_State *lua) {
    DrawContext &drawContext = DrawContext::getInstance();

    // Get the desired thickness.
    float thickness = (unsigned char) luaL_checknumber(lua, 1);

    // Set the thickness to the desired value.
    drawContext.rectangleShape.setOutlineThickness(thickness);
    drawContext.polygonShape.setOutlineThickness(thickness);

    return 0;
}

/*
 * Lua Function: draw.setRotation(angle)
 * Description:  Sets the rotation for shapes being drawn in degrees.
 * Parameters:   angle - the rotation of shapes in degrees
 * Returns:      None.
 */
int DrawContext::setRotation(lua_State *lua) {
    DrawContext &drawContext = DrawContext::getInstance();

    // Get the desired angle.
    float angle = (unsigned char)luaL_checknumber(lua, 1);

    // Set the angle to the desired value.
    drawContext.rectangleShape.setRotation(angle);
    drawContext.polygonShape.setRotation(angle);

    return 0;
}

/*
 * Lua Function: draw.rectangle(x, y, width, height)
 * Description:  Draws a rectangle at (x, y) with dimensions (width, height).
 * Parameters:   x - the x-coordinate of the top left corner
 *               y - the y-coordinate of the top left corner
 *               width - how wide the rectangle is in pixels
 *               height - how tall the rectangle is in pixels
 * Returns:      None.
 */
int DrawContext::rectangle(lua_State *lua) {
    DrawContext &drawContext = DrawContext::getInstance();

    // Make sure there is a window to draw to.
    if (!drawContext.window) {
        return 0;
    }

    // Get the parameters for the function.
    float x = (float) luaL_checknumber(lua, 1);
    float y = (float) luaL_checknumber(lua, 2);
    float width = (float) luaL_checknumber(lua, 3);
    float height = (float) luaL_checknumber(lua, 4);

    // Set the properties of the rectangle to the desired values.
    drawContext.rectangleShape.setPosition(x, y);
    drawContext.rectangleShape.setSize(sf::Vector2f(width, height));

    drawContext.window->draw(drawContext.rectangleShape);

    return 0;
}

/*
 * Lua Function: draw.polygon(x, y, radius, sides)
 * Description:  Draws a n-gon (where n is sides) on the screen at (x, y) with
 *               a given radius.
 * Parameters:   x - the x-coordinate of the polygon
 *               y - the y-coordinate of the polygon
 *               radius - the distance from each side to the center
 *               sides - the number of sides for the polygon
 * Returns:      None.
 */
int DrawContext::polygon(lua_State *lua) {
    DrawContext &drawContext = DrawContext::getInstance();

    // Make sure there is a window to draw to.
    if (!drawContext.window) {
        return 0;
    }

    // Get the parameters of the function.
    float x = (float)luaL_checknumber(lua, 1);
    float y = (float)luaL_checknumber(lua, 2);
    float radius = (float)luaL_checknumber(lua, 3);
    int sides = 30;

    if (lua_gettop(lua) > 3) {
        sides = (int) luaL_checknumber(lua, 4);
    }

    // Set the properties of the polygon to fit the desired values.
    drawContext.polygonShape.setPosition(x, y);
    drawContext.polygonShape.setRadius(radius);
    drawContext.polygonShape.setPointCount(sides);

    // Draw the polygon.
    drawContext.window->draw(drawContext.polygonShape);

    return 0;
}

/*
 * Lua Function: draw.line(x1, y1, x2, y2)
 * Description:  Draws a line segment from (x1, y1) to (x2, y2).
 * Parameters:   x1 - the x-coordinate of the starting point
 *               y1 - the y-coordinate of the starting point
 *               x2 - the x-coordinate of the ending point
 *               y2 - the y-coordinate of the ending point
 * Returns:      None.
 */
int DrawContext::line(lua_State *lua) {
	DrawContext &drawContext = DrawContext::getInstance();
	
	// if window doesn't exist
	if (!drawContext.window) {
		return 0;
	}

	// save initial rectangle rotation
	float initRotation = drawContext.rectangleShape.getRotation();

	// parameters of the line
	float x1 = (float)luaL_checknumber(lua, 1);
	float y1 = (float)luaL_checknumber(lua, 2);
	float x2 = (float)luaL_checknumber(lua, 3);
	float y2 = (float)luaL_checknumber(lua, 4);

	// Pythag to find length of line
	float xDelta = x2 - x1;
	float yDelta = y2 - y1;
	float width = sqrt((xDelta * xDelta) + (yDelta * yDelta));

	// set length of line
	drawContext.rectangleShape.setPosition(x1, y1);
	drawContext.rectangleShape.setSize(sf::Vector2f(width, 1));

	// rotate to correct spot
	drawContext.rectangleShape.rotate(RAD2DEG * atan2(yDelta, xDelta));
	// draw the line
	drawContext.window->draw(drawContext.rectangleShape);

	//set rotation back to its initial value
	drawContext.rectangleShape.setRotation(initRotation);

	return 0;
}


/* 
 * Lua Function: draw.text(x, y, string, font)
 * Description:	 Draws the string beginning at x,y with the given font
 * Parameters:	 x - the x-coordinate of the starting point
 *				 y - the y-coordinate of the starting point 
 *				 string - piece of text that is drawn
 *				 font - font of the text
 * Returns:      None.
 */
int DrawContext::text(lua_State *lua) {
	DrawContext &drawContext = DrawContext::getInstance();

	// Check if window to draw onto exists
	if (!drawContext.window) {
		return 0;
	}

	// Get the parameters of the function.
	float x = (float)luaL_checknumber(lua, 1);
	float y = (float)luaL_checknumber(lua, 2);
	std::string text(luaL_checkstring(lua, 3));
	std::string fontName(luaL_checkstring(lua, 4));
	unsigned int size = (unsigned int)luaL_checknumber(lua, 5);

	std::unordered_map<std::string, sf::Font>::const_iterator it;
	it = drawContext.fontMap.find(fontName);

	if (it == drawContext.fontMap.end()) {
		sf::Font font;

		if (font.loadFromFile("fonts/" + fontName + ".ttf")) {
			std::cerr << fontName << " could not be found!" << std::endl;
		}
	
		drawContext.fontMap[fontName] = font;
	}

	drawContext.textShape.setPosition(x, y);
	drawContext.textShape.setString(text);
	drawContext.textShape.setFont(drawContext.fontMap[fontName]);
	drawContext.textShape.setCharacterSize(size);
	

	drawContext.window->draw(drawContext.textShape);

	return 0;
}

// Set up a library mapping from C++ to Lua.
static const luaL_Reg draw[] = {
    {"setColor", DrawContext::setColor},
    {"setOutlineColor", DrawContext::setOutlineColor},
    {"setOutlineThickness", DrawContext::setOutlineThickness},
    {"setRotation", DrawContext::setRotation},
    {"rectangle", DrawContext::rectangle},
    {"polygon", DrawContext::polygon},
    {"line", DrawContext::line},
	{"text", DrawContext::text},
    {0, 0} // Sentinel
};

void DrawContext::bind(lua_State *lua) {
    // Create the draw library with the DrawContext functions.
    luaL_newlib(lua, draw);
    lua_setglobal(lua, "draw");
}

void DrawContext::reset() {
    rectangleShape.setRotation(0);
    polygonShape.setRotation(0);
}