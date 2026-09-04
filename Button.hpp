#pragma once
#include <SFML/Graphics.hpp>

class Button {
public:
	Button(sf::Vector2f pos, const sf::Texture& iconTexture, 
		sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
	
	Button(sf::Vector2f pos, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);

	void update(const sf::Vector2i& mousePos, bool isClicked);
	void updateHover(const sf::Vector2i& mousePos);
	void updatePressed(const sf::Vector2i& mousePos);
	bool isClicked(const sf::Vector2i& mousePos, sf::Mouse::Button targetButton, const sf::Event& event);
	void render(sf::RenderWindow& window);

	bool isHovered() const { return wasHovered; }

	void setActive(bool active) { isActive = active; }
	void toggleActive() { isActive = !isActive; }
	bool getActive() const { return isActive; }

private:
	bool wasHovered = false;
	bool isActive = false;
	sf::RectangleShape shape;
	sf::Sprite icon;
	sf::Color idle;
	sf::Color hover;
	sf::Color active;
};