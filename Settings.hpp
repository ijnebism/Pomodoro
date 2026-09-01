#pragma once
#include "State.hpp"

class Settings : public State {
public:
	Settings(const sf::Font& font);

    void handleInput(sf::RenderWindow& window) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;

private:
    std::array<sf::Text, 1> settings;
};