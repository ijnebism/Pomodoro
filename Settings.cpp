#include "Settings.hpp"
#include <iostream>

Settings::Settings(const sf::Font& font, const sf::Texture& clockTexture, const sf::Texture& settingsTexture, const sf::Texture& hideTexture, const sf::Texture& moveTexture) :
	settingsButton(sf::Vector2f({ 125,5 }), settingsTexture, sf::Color(128, 128, 128), sf::Color(90, 90, 90), sf::Color::Green),
	timerButton(sf::Vector2f({ 25,5 }), clockTexture, sf::Color(128, 128, 128), sf::Color(90, 90, 90), sf::Color::Green),
	hideButton(sf::Vector2f({ 175,5 }), hideTexture, sf::Color(128, 128, 128), sf::Color(90, 90, 90), sf::Color::Green),
	moveButton(sf::Vector2f({ 75,5 }), moveTexture, sf::Color(128, 128, 128), sf::Color(90, 90, 90), sf::Color::Green)
{

	settingsButton.setActive(true);

}

void Settings::handleInput(sf::RenderWindow& window) {
	while (const std::optional event = window.pollEvent()) {
		if (event->is<sf::Event::Closed>()) {
			window.close();
		}

		sf::Vector2i mousePos = sf::Mouse::getPosition(window);

		if (timerButton.isClicked(mousePos, sf::Mouse::Button::Left, *event)) {
			nextState = StateType::Timer;

		}
		if (hideButton.isClicked(mousePos, sf::Mouse::Button::Left, *event)) {
			hideButton.toggleActive();
		}
	}
}

void Settings::update(float dt, sf::RenderWindow& window) {
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	settingsButton.updateHover(mousePos);
	timerButton.updateHover(mousePos);
	hideButton.updateHover(mousePos);
	moveButton.updateHover(mousePos);

	moveButton.updatePressed(mousePos);

	if (moveButton.getActive()) {
		sf::Vector2i currentScreenPos = sf::Mouse::getPosition();
		if (!wasDragging) {
			dragStartScreenPos = currentScreenPos;
			dragStartWindowPos = window.getPosition();
			wasDragging = true;
		}
		else {
			sf::Vector2i delta = currentScreenPos - dragStartScreenPos;
			window.setPosition(dragStartWindowPos + delta);
		}
	}
	else {
		wasDragging = false;
	}
}

void Settings::render(sf::RenderWindow& window) {
	sf::Vector2u windowSize = window.getSize();
	window.clear(sf::Color::Transparent);


	if (!hideButton.getActive()) {

		settingsButton.render(window);
		timerButton.render(window);
		moveButton.render(window);

	}

	hideButton.render(window);
	window.display();
}

bool Settings::isMouseOverUI(const sf::Vector2i& mousePos) const {
	return settingsButton.isHovered() || timerButton.isHovered() || hideButton.isHovered() || moveButton.isHovered();
}