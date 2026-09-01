#include <SFML/Graphics.hpp>
#include <dwmapi.h>
#include "State.hpp"
#include "Timer.hpp"

#pragma comment(lib, "dwmapi.lib")


int main() {
	sf::RenderWindow window(sf::VideoMode({800, 600}), "Pomodoro", sf::Style::None);
	sf::Clock clock;
	sf::Font font;

	// Transparent bg setup
	HWND hwnd = static_cast<HWND>(window.getNativeHandle());

	SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_CAPTION);
	LONG exStyle = GetWindowLong(hwnd, GWL_EXSTYLE);
	SetWindowLong(hwnd, GWL_EXSTYLE, exStyle | WS_EX_LAYERED | WS_EX_TRANSPARENT);

	MARGINS margins = { -1 };
	DwmExtendFrameIntoClientArea(hwnd, &margins);

	SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	//state changer
	std::unique_ptr<State> currentState = std::make_unique<Timer>(font);

	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {
			if (event ->is<sf::Event::Closed>()) {
				window.close();
			}
		}
		
		currentState->handleInput(window);
		currentState->update(clock.restart().asSeconds());
		currentState->render(window);
	};
}