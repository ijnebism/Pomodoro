#include <SFML/Graphics.hpp>
#include <dwmapi.h>
#include <iostream>

#pragma comment(lib, "dwmapi.lib")


int main() {
	sf::RenderWindow window(sf::VideoMode({800, 600}), "Pomodoro", sf::Style::None);

	HWND hwnd = static_cast<HWND>(window.getNativeHandle());

	SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_CAPTION);

	MARGINS margins = { -1 };
	DwmExtendFrameIntoClientArea(hwnd, &margins);

	SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {
			if (event ->is<sf::Event::Closed>()) {
				window.close();
			}
		}
		window.clear(sf::Color::Transparent);

		sf::CircleShape circle(50);
		circle.setFillColor(sf::Color::Green);
		circle.setPosition({ 375.f, 275.f });
		window.draw(circle);
		window.display();
	};
}