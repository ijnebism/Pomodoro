#include "Timer.hpp"

Timer::Timer(const sf::Font& font, const sf::Texture& clockTexture, const sf::Texture& settingsTexture, const sf::Texture& hideTexture) :
time(font),
settingsButton(sf::Vector2f({100,50}), settingsTexture, sf::Color::Black, sf::Color::Blue, sf::Color::Green),
timerButton(sf::Vector2f({0,50 }), clockTexture, sf::Color::Black, sf::Color::Blue, sf::Color::Green),
hideButton(sf::Vector2f({200,50 }), hideTexture, sf::Color::Black, sf::Color::Blue, sf::Color::Green)
{

	time.setString("25:00");
	time.setCharacterSize(48);
	time.setOutlineColor(sf::Color::Black);
	time.setOutlineThickness(2);
	time.setFillColor(sf::Color::White);
}

void Timer::handleInput(sf::RenderWindow& window) {
	while (const std::optional event = window.pollEvent()) {
		if (event->is<sf::Event::Closed>()) {
			window.close();
		}

		// Update buttons
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		settingsButton.update(mousePos, settingsButton.isClicked(mousePos, sf::Mouse::Button::Left, *event));
		timerButton.update(mousePos, timerButton.isClicked(mousePos, sf::Mouse::Button::Left, *event));
		hideButton.update(mousePos, hideButton.isClicked(mousePos, sf::Mouse::Button::Left, *event));

	}
}

void Timer::update(float dt) {
	// None atm
}

void Timer::render(sf::RenderWindow& window) {
	window.clear(sf::Color::White);
	window.draw(time);
	settingsButton.render(window);
	timerButton.render(window);
	hideButton.render(window);
	window.display();
}