#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "State.hpp"
#include "Button.hpp"

class Statistics : public State {
public:
    Statistics(const sf::Font& font, const sf::Texture& clockTexture, const sf::Texture& settingsTexture, const sf::Texture& hideTexture, const sf::Texture& moveTexture, const sf::Texture& resetTexture);

    void handleInput(sf::RenderWindow& window) override;
    void update(float dt, sf::RenderWindow& window) override;
    void render(sf::RenderWindow& window) override;

    bool isMouseOverUI(const sf::Vector2i& mousePos) const override;

    void updateTimer(float dt);

private:
    Button settingsButton;
    Button timerButton;
    Button hideButton;
    Button moveButton;

    bool wasDragging = false;
    sf::Vector2i dragStartScreenPos;
    sf::Vector2i dragStartWindowPos;
};