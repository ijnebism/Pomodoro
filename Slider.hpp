#pragma once
#include <SFML/Graphics.hpp>

class Slider {
public:
	Slider(sf::Vector2f pos, sf::Vector2f size, float minValue, float maxValue, float initialValue);

	void handleInput(const sf::Event& event, sf::RenderWindow& window);
	void render(sf::RenderWindow& window);
	void update(const sf::Vector2i& mousePos);

	float getValue() const { return value; }
	void setValue(float newValue);

	bool isHovered(const sf::Vector2i& mousePos) const;

private:
	void updateHandlePosition();

	sf::RectangleShape slider;
	sf::CircleShape handle;
	
	float value;
	float minValue;
	float maxValue;

	sf::Vector2f position;
	sf::Vector2f size;

	bool isDragging = false;
	bool wasHovered = false;
};