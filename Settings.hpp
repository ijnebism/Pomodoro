#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Button.hpp"
#include "TextField.hpp"
#include "Slider.hpp"

class Settings : public State {
public:
    Settings(const sf::Font& font, const sf::Texture& clockTexture, const sf::Texture& settingsTexture, const sf::Texture& hideTexture, const sf::Texture& moveTexture);

    void handleInput(sf::RenderWindow& window) override;
    void update(float dt, sf::RenderWindow& window) override;
    void render(sf::RenderWindow& window) override;

    bool isMouseOverUI(const sf::Vector2i& mousePos) const override;

private:
	//Header Buttons
    Button settingsButton;
    Button timerButton;
    Button hideButton;
    Button moveButton;

    // Timers
    TextField workduration;
    TextField breakduration;
	sf::Text workLabel;
	sf::Text breakLabel;

    // Toggle Starts
	Button workToggle;
	Button breakToggle;
	sf::Text workToggleLabel;
	sf::Text breakToggleLabel;

    // Audio
    sf::Text audioLabel;
    sf::Text volumeLabel;
    Slider audioSlider;

	// Dragging
    bool wasDragging = false;
    sf::Vector2i dragStartScreenPos;
    sf::Vector2i dragStartWindowPos;
};