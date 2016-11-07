#include <cmath>
#include <iostream>
#include "drawcontext.h"

#if _DEBUG
#include "debug_stackdump.h"
#endif

#define RAD2DEG (180.0f / 3.14159265f)

static inline void setFontProperty(lua_State *lua, unsigned int &flags,
const char *name, int style) {
    int top = lua_gettop(lua);

    lua_pushstring(lua, name);
    lua_gettable(lua, 4 - top);

    if (!lua_isnoneornil(lua, top)) {
        flags |= style;
    }

    lua_pop(lua, 1);
}

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
 * Lua Function: draw.createFont(name, fontName, size, style)
 * Description:  Sets up a font to be used for drawing text.
 * Parameters:   name - a string identifier for the font
 *               fontName - the file that contains the font
 *               size - the height of each character
 *               style - a table containing style properties for the font
 */
int DrawContext::createFont(lua_State *lua) {
    DrawContext &drawContext = DrawContext::getInstance();

    // Get the parameters.
    std::string name(luaL_checkstring(lua, 1));
    std::string fontName(luaL_checkstring(lua, 2));
    unsigned int size = (unsigned int) luaL_checknumber(lua, 3);
    unsigned int style = sf::Text::Style::Regular;
    int top = lua_gettop(lua);

    // Set the font flags to match the values of the style table.
    if (top > 3) {

        setFontProperty(lua, style, "bold", sf::Text::Style::Bold);
        setFontProperty(lua, style, "italic", sf::Text::Style::Italic);
        setFontProperty(lua, style, "underlined", sf::Text::Style::Underlined);
        setFontProperty(lua, style, "strikeThrough",
                        sf::Text::Style::StrikeThrough);
    }

    // Remove duplicate entry for the font.
    TextMap::const_iterator it = drawContext.textMap.find(name);

    if (it != drawContext.textMap.end()) {
        drawContext.textMap.erase(it);
    }

    // Get the font to use from the font name.
    FontMap::const_iterator fontIt = drawContext.fontMap.find(fontName);

    if (fontIt == drawContext.fontMap.end()) {
        sf::Font font;

        if (!font.loadFromFile("fonts/" + fontName)) {
            std::cerr << "Failed to load font \"" << fontName << "\" from disk!"
                << std::endl;

            return 0;
        }

        drawContext.fontMap[fontName] = font;
    }

    // Add a text object that holds the font to the font map.
    sf::Text text("", drawContext.fontMap[fontName], size);
    text.setStyle(style);

    drawContext.textMap[name] = text;

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

    // Check if the font exists.
    TextMap::const_iterator it = drawContext.textMap.find(fontName);

    if (it == drawContext.textMap.end()) {
        lua_pushstring(lua, (fontName + " is not a valid font").c_str());
        lua_error(lua);

        return 0;
    }

    // Draw the shape with the given properties.
    sf::Text &textShape = drawContext.textMap[fontName];

    textShape.setPosition(x, y);
    textShape.setString(text);

    drawContext.window->draw(textShape);

	return 0;
}

// Set up a library mapping from C++ to Lua.
static const luaL_Reg draw[] = {
    {"createFont", DrawContext::createFont},
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