#pragma once
#include "State.hpp"

class Timer : public State {
public:
    Timer(const sf::Font& font);

    void handleInput(sf::RenderWindow& window) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;

private:
    sf::Text time;
};