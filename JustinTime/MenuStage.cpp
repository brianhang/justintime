#include "menustage.h"

#define PI 3.1415f

using namespace sf;

MenuStage::MenuStage() {
	time = 0.0f;

	if (face.loadFromFile("res/textures/justin.png")) {
		centerFace.setTexture(face);
		centerFace.setScale(sf::Vector2f(3.0f, 3.0f));
		centerFace.setPosition(sf::Vector2f(320.0f, 240.0f));
		centerFace.setOrigin(sf::Vector2f(34.0f, 43.5f));
	}

	if (font.loadFromFile("res/fonts/pressstart2p.ttf")) {
		title.setFont(font);
		title.setString("JUSTIN TIME");
		title.setPosition(sf::Vector2f(320.0f, 120.0f));
		title.setOrigin(title.getLocalBounds().width / 2, title.getLocalBounds().height / 2);
		title.setCharacterSize(32);
	}
}

void MenuStage::update(float deltaTime) {
	time += deltaTime;

	centerFace.setRotation(sin(time * 5.0f) * 30.0f);
}

void MenuStage::onEvent(const sf::Event &e) {
	if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Space) {
		centerFace.setColor(sf::Color::Red);
	}
}

void MenuStage::draw(sf::RenderWindow &window) {
	window.draw(centerFace);

	float j;
	float k;

	for (int i = 0; i < 5; i++) {
		k = i / 5.0f;
		j = k * PI * 0.33f;

		Uint32 brightness = (Uint32)(k * 255.0f);

		title.setRotation(sin(time * 2.5f + j) * 10.0f);
		title.setFillColor(sf::Color(brightness, brightness, brightness));
		window.draw(title);
	}
}