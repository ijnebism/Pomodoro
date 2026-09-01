#include <SFML/Graphics.hpp>
#include <dwmapi.h>
#include "State.hpp"
#include "Timer.hpp"

#pragma comment(lib, "dwmapi.lib")


int main() {
	sf::RenderWindow window(sf::VideoMode({300, 200}), "Pomodoro", sf::Style::None);
	sf::Clock clock;
	sf::Font font;
	sf::Texture clockTexture;
	sf::Texture settingsTexture;
	sf::Texture hideTexture;

	// Load assets
	if (!font.openFromFile("./assets/ArchivoBlack-Regular.ttf")) {
		return -1;
	}

	if (!clockTexture.loadFromFile("./assets/clock.png")) {
		return -1;
	}

	if (!settingsTexture.loadFromFile("./assets/settings.png")) {
		return -1;
	}

	if (!hideTexture.loadFromFile("./assets/hidden.png")) {
		return -1;
	}

	// Transparent bg setup
	HWND hwnd = static_cast<HWND>(window.getNativeHandle());

	SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_CAPTION);
	LONG exStyle = GetWindowLong(hwnd, GWL_EXSTYLE);
	SetWindowLong(hwnd, GWL_EXSTYLE, exStyle | WS_EX_LAYERED | WS_EX_TRANSPARENT);

	MARGINS margins = { -1 };
	DwmExtendFrameIntoClientArea(hwnd, &margins);

	SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	//state changer
	std::unique_ptr<State> currentState = std::make_unique<Timer>(font, clockTexture, settingsTexture, hideTexture);

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