#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Button.hpp"

class Settings : public State {
public:
    Settings(const sf::Font& font, const sf::Texture& clockTexture, const sf::Texture& settingsTexture, const sf::Texture& hideTexture, const sf::Texture& moveTexture);

    void handleInput(sf::RenderWindow& window) override;
    void update(float dt, sf::RenderWindow& window) override;
    void render(sf::RenderWindow& window) override;

    bool isMouseOverUI(const sf::Vector2i& mousePos) const override;

private:
    Button settingsButton;
    Button timerButton;
    Button hideButton;
    Button moveButton;

    bool wasDragging = false;
    sf::Vector2i dragStartScreenPos;
    sf::Vector2i dragStartWindowPos;
};