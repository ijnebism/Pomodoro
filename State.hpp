#pragma once
#include <SFML/Graphics.hpp>

enum class StateType {
	None,
	Timer,
	Settings
};

class State {
public:
	virtual ~State() = default;
	virtual void handleInput(sf::RenderWindow& window) = 0;
	virtual void update(float dt, sf::RenderWindow& window) = 0;
	virtual void render(sf::RenderWindow& window) = 0;

	StateType getNextState() const { return nextState; }
	void resetNextState() { nextState = StateType::None; }

	virtual bool isMouseOverUI(const sf::Vector2i& mousePos) const = 0;

protected:
	StateType nextState = StateType::None;
};