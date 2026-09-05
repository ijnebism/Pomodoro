#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Button.hpp"
#include "SettingsData.hpp" 

class Timer : public State {
public:
    Timer(const sf::Font& font, const sf::Texture& clockTexture, const sf::Texture& settingsTexture, const sf::Texture& hideTexture, const sf::Texture& moveTexture, const SettingsData& settingsData);

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

    bool wasDragging = false;
    sf::Vector2i dragStartScreenPos;
    sf::Vector2i dragStartWindowPos;

	SettingsData settingsData;
};