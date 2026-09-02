#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Button.hpp"

class Timer : public State {
public:
    Timer(const sf::Font& font, const sf::Texture& clockTexture, const sf::Texture& settingsTexture, const sf::Texture& hideTexture, const sf::Texture& moveTexture);

    void handleInput(sf::RenderWindow& window) override;
    void update(float dt, sf::RenderWindow& window) override;
    void render(sf::RenderWindow& window) override;

	bool isMouseOverUI(const sf::Vector2i& mousePos) const override;

private:
    sf::Text time;
    Button settingsButton;
	Button timerButton;
	Button hideButton;
	Button moveButton;
};