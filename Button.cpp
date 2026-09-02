#include "Button.hpp"

Button::Button(sf::Vector2f pos, const sf::Texture& iconTexture,
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
	: idle(idleColor), hover(hoverColor), active(activeColor), icon(iconTexture) {
	shape.setPosition(pos);
	shape.setSize(sf::Vector2f(30.f, 30.f));
	shape.setFillColor(idle);

	float padding = 8.f;
	sf::Vector2f targetSize = shape.getSize() - sf::Vector2f(padding * 2, padding * 2);

	sf::FloatRect iconBounds = icon.getLocalBounds();
	float scaleX = targetSize.x / iconBounds.size.x;
	float scaleY = targetSize.y / iconBounds.size.y;
	float scale = std::min(scaleX, scaleY);
	icon.setScale(sf::Vector2f(scale, scale));

	icon.setOrigin(sf::Vector2f(iconBounds.size.x / 2.f, iconBounds.size.y / 2.f));
	icon.setPosition(shape.getPosition() + shape.getSize() / 2.f);


};

void Button::update(const sf::Vector2i& mousePos, bool isClicked) {
	sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
	if (shape.getGlobalBounds().contains(mousePosF)) {
		shape.setFillColor(hover);
		if (isClicked) {
			shape.setFillColor(active);
		}
	} else {
		shape.setFillColor(idle);
	}
}

void Button::updateHover(const sf::Vector2i& mousePos) {
	sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
	bool currentlyHovered = shape.getGlobalBounds().contains(mousePosF);
	wasHovered = currentlyHovered;
	if (isActive) {
		shape.setFillColor(active);
	}
	else if (currentlyHovered) {
		shape.setFillColor(hover);
	}
	else {
		shape.setFillColor(idle);
	}
}

void Button::updatePressed(const sf::Vector2i& mousePos) {
	sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
	bool overButton = shape.getGlobalBounds().contains(mousePosF);
	bool pressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
	isActive = overButton && pressed;
}

void Button::render(sf::RenderWindow& window) {
	window.draw(shape);
	window.draw(icon);
}

bool Button::isClicked(const sf::Vector2i& mousePos, sf::Mouse::Button targetButton, const sf::Event& event) {
	sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

	if (shape.getGlobalBounds().contains(mousePosF)) {
		if (event.is<sf::Event::MouseButtonReleased>()) {
			if (event.getIf<sf::Event::MouseButtonReleased>()->button == targetButton) {
				return true;
			}
		}
	}
	return false;
}