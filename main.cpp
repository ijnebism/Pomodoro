#include <SFML/Graphics.hpp>
#include <dwmapi.h>
#include "State.hpp"
#include "Timer.hpp"

#pragma comment(lib, "dwmapi.lib")


int main() {
	sf::RenderWindow window(sf::VideoMode({230, 200}), "Pomodoro", sf::Style::None);
	sf::Clock clock;
	sf::Font font;
	sf::Texture clockTexture;
	sf::Texture settingsTexture;
	sf::Texture hideTexture;
	sf::Texture moveTexture;

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

	if (!moveTexture.loadFromFile("./assets/move.png")) {
		return -1;
	}

	// Transparent bg setup
	HWND hwnd = static_cast<HWND>(window.getNativeHandle());

	SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_CAPTION);
	LONG exStyle = GetWindowLong(hwnd, GWL_EXSTYLE);
	SetWindowLong(hwnd, GWL_EXSTYLE, exStyle | WS_EX_LAYERED);

	MARGINS margins = { -1 };
	DwmExtendFrameIntoClientArea(hwnd, &margins);

	SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	//state changer
	std::unique_ptr<State> currentState = std::make_unique<Timer>(font, clockTexture, settingsTexture, hideTexture, moveTexture);

	sf::Vector2u desktopSize = sf::VideoMode::getDesktopMode().size;

	window.setPosition(sf::Vector2i(desktopSize.x - window.getSize().x, 0));


	bool wasClickThrough = false;

	while (window.isOpen()) {
		currentState->handleInput(window);
		currentState->update(clock.restart().asSeconds(), window);

		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		bool overInteractive = currentState->isMouseOverUI(mousePos);

		if (overInteractive == wasClickThrough) {
			LONG exStyle = GetWindowLong(hwnd, GWL_EXSTYLE);
			if (overInteractive) {
				SetWindowLong(hwnd, GWL_EXSTYLE, exStyle & ~WS_EX_TRANSPARENT);
			}
			else {
				SetWindowLong(hwnd, GWL_EXSTYLE, exStyle | WS_EX_TRANSPARENT);
			}
			wasClickThrough = !overInteractive;
		}

		currentState->render(window);
	}
}