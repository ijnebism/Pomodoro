#include "Slider.hpp"

Slider::Slider(sf::Vector2f pos, sf::Vector2f size, float minValue, float maxValue, float initialValue)
	: position(pos), size(size), minValue(minValue), maxValue(maxValue), value(initialValue) {
	slider.setPosition(pos);
	slider.setSize({size.x, size.y/4.f});
	slider.setFillColor(sf::Color(200, 200, 200));
	slider.setOutlineColor(sf::Color::Black);
	slider.setOutlineThickness(2.f);
	handle.setRadius(size.y / 2.f);
	handle.setFillColor(sf::Color(100, 100, 100));
	handle.setOutlineColor(sf::Color::Black);
	handle.setOutlineThickness(2.f);
	setValue(initialValue);
}

void Slider::handleInput(const sf::Event& event, sf::RenderWindow& window) {
	if (event.is<sf::Event::MouseButtonPressed>()) {
		sf::Vector2f mousePosF(static_cast<float>(sf::Mouse::getPosition(window).x), static_cast<float>(sf::Mouse::getPosition(window).y));
		if (handle.getGlobalBounds().contains(mousePosF)) {
			isDragging = true;
		}
	}
	else if (event.is<sf::Event::MouseButtonReleased>()) {
		isDragging = false;
	}
}

void Slider::update(const sf::Vector2i& mousePos) {
	sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
	wasHovered = handle.getGlobalBounds().contains(mousePosF);
	if (isDragging) {
		float newValue = minValue + (maxValue - minValue) * ((mousePosF.x - position.x) / size.x);
		setValue(newValue);
	}
}

void Slider::render(sf::RenderWindow& window) {
	window.draw(slider);
	window.draw(handle);
}

void Slider::setValue(float newValue) {
	value = std::clamp(newValue, minValue, maxValue);
	updateHandlePosition();
}

bool Slider::isHovered(const sf::Vector2i& mousePos) const {
	sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
	return handle.getGlobalBounds().contains(mousePosF);
}

void Slider::updateHandlePosition() {
	float handleX = position.x + (value - minValue) / (maxValue - minValue) * size.x - handle.getRadius();
	handle.setPosition({ handleX, position.y - 1.f - size.y / 4.f });
}

