#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Button.hpp"
#include "SettingsData.hpp" 

enum TimerPhase {
	Work,
	Break
};

class Timer : public State {
public:
    Timer(const sf::Font& font, const sf::Texture& clockTexture, const sf::Texture& settingsTexture, const sf::Texture& hideTexture, const sf::Texture& moveTexture, const SettingsData& settingsData, const sf::Texture& startTexture, const sf::Texture& resetTexture);

    void handleInput(sf::RenderWindow& window) override;
    void update(float dt, sf::RenderWindow& window) override;
    void render(sf::RenderWindow& window) override;

	bool isMouseOverUI(const sf::Vector2i& mousePos) const override;

    void updateSettings(const SettingsData& newSettings);

private:
    sf::Text time;
    sf::Text status;
    Button settingsButton;
	Button timerButton;
	Button hideButton;
	Button moveButton;
    Button startButton;
	Button resetButton;

	TimerPhase currentPhase = TimerPhase::Work;
	void switchPhase();

    int secondsRemaining;
    float accumulatedTime = 0.f;
    void resetState();

    bool wasDragging = false;
    sf::Vector2i dragStartScreenPos;
    sf::Vector2i dragStartWindowPos;

	SettingsData settingsData;
};