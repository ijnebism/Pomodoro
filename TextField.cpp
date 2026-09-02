#include "TextField.hpp"

TextField::TextField(const sf::Font& font, sf::Vector2f position, sf::Vector2f size)
	: text(font) {
	shape.setPosition(position);
	shape.setSize(size);
	shape.setFillColor(sf::Color(200, 200, 200));
	shape.setOutlineColor(sf::Color::Black);
	shape.setOutlineThickness(2.f);
	text.setFont(font);
	text.setCharacterSize(static_cast<unsigned int>(size.y * 0.6f));
	text.setFillColor(sf::Color::Black);
	text.setPosition({ position.x + 5.f, position.y + (size.y - text.getCharacterSize()) / 2.f });
}

void TextField::handleInput(const sf::Event& event, sf::RenderWindow& window) {
	if (event.is<sf::Event::MouseButtonReleased>()) {
		sf::Vector2f mousePosF(static_cast<float>(sf::Mouse::getPosition(window).x), static_cast<float>(sf::Mouse::getPosition(window).y));
		focused = shape.getGlobalBounds().contains(mousePosF);
	}

	if (focused) {
		if (const auto* textEvent = event.getIf<sf::Event::TextEntered>()) {
			char enteredChar = static_cast<char>(textEvent->unicode);
			if (enteredChar == 8) {
				if (!buffer.empty()) {
					buffer.pop_back();
				}

			}
			else if (std::isdigit(enteredChar) && buffer.size() < 3) {
				buffer += enteredChar;
			}
		}
		text.setString(buffer);
	}
	
}

void TextField::render(sf::RenderWindow& window) {
	window.draw(shape);
	window.draw(text);
}

int TextField::getValue() const {
	try {
		return std::stoi(buffer);
	}
	catch (const std::invalid_argument&) {
		return 0;
	}
}

