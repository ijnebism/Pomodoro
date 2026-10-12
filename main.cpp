#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <dwmapi.h>
#include <shobjidl.h>
#include "State.hpp"
#include "Timer.hpp"
#include "Settings.hpp"
#include "SettingsData.hpp"
#include "Path.hpp"

#pragma comment(lib, "dwmapi.lib")

LRESULT CALLBACK TrayProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_APP + 1) {
		if (lParam == WM_LBUTTONUP) {
			MessageBeep(MB_OK);
		}
		return 0;
	}
	return DefWindowProcW(hwnd, msg, wParam, lParam);
}

HWND createTrayWindow()
{
	WNDCLASSW wc{};
	wc.lpfnWndProc = TrayProc;             
	wc.hInstance = GetModuleHandleW(nullptr);
	wc.lpszClassName = L"PomodoroTray";
	RegisterClassW(&wc);

	return CreateWindowExW(0, L"PomodoroTray", L"", 0,
		0, 0, 0, 0,
		HWND_MESSAGE,
		nullptr, wc.hInstance, nullptr);
}

int main() {
	sf::RenderWindow window(sf::VideoMode({230, 200}), "Pomodoro", sf::Style::None);
	window.setFramerateLimit(30);
	//window.setVisible(false);
	sf::Clock clock;
	sf::Font font;
	sf::Texture clockTexture;
	sf::Texture settingsTexture;
	sf::Texture hideTexture;
	sf::Texture moveTexture;
	sf::Texture startTexture;
	sf::Texture resetTexture;
	sf::SoundBuffer alarmBuffer;

	SettingsData settingsData;
	settingsData.loadFromFile();

	std::filesystem::path assetsDir = getExecutablePath() / "assets";

	// Load assets
	if (!font.openFromFile(assetsDir / "ArchivoBlack-Regular.ttf")) {
		return -1;
	}

	if (!clockTexture.loadFromFile(assetsDir / "clock.png")) {
		return -1;
	}

	if (!settingsTexture.loadFromFile(assetsDir / "settings.png")) {
		return -1;
	}

	if (!hideTexture.loadFromFile(assetsDir / "hidden.png")) {
		return -1;
	}

	if (!moveTexture.loadFromFile(assetsDir / "move.png")) {
		return -1;
	}

	if (!startTexture.loadFromFile(assetsDir / "play.png")) {
		return -1;
	}

	if (!resetTexture.loadFromFile(assetsDir / "reset.png")) {
		return -1;
	}

	if (!alarmBuffer.loadFromFile(assetsDir / "alarm.wav")) {
		return -1;
	}
	sf::Sound alarmSound(alarmBuffer);

	// Transparent bg setup
	HWND hwnd = static_cast<HWND>(window.getNativeHandle());

	ShowWindow(hwnd, SW_HIDE);

	SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_CAPTION);
	LONG exStyle = GetWindowLong(hwnd, GWL_EXSTYLE);

	exStyle |= WS_EX_LAYERED | WS_EX_TOOLWINDOW; 
	exStyle &= ~WS_EX_APPWINDOW;

	SetWindowLong(hwnd, GWL_EXSTYLE, exStyle);
	SetLayeredWindowAttributes(hwnd, 0, 255, LWA_ALPHA);

	MARGINS margins = { -1 };
	DwmExtendFrameIntoClientArea(hwnd, &margins);

	SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	ShowWindow(hwnd, SW_SHOW);

	sf::Vector2u desktopSize = sf::VideoMode::getDesktopMode().size;

	window.setPosition(sf::Vector2i(desktopSize.x - window.getSize().x, 0));


	bool wasClickThrough = false;

	// State management
	Timer timerstate(font, clockTexture, settingsTexture, hideTexture, moveTexture ,settingsData, startTexture, resetTexture, alarmSound);
	Settings settingsstate(font, clockTexture, settingsTexture, hideTexture, moveTexture, settingsData);

	State* currentState = &timerstate;

	HWND trayHwnd = createTrayWindow();

	NOTIFYICONDATAW nid{};

	nid.cbSize = sizeof(nid);
	nid.hWnd = trayHwnd;
	nid.uID = 101;

	nid.uCallbackMessage = WM_APP + 1;
	nid.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wcscpy_s(nid.szTip, L"Pomodoro");
	nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;

	Shell_NotifyIcon(NIM_ADD, &nid);

	while (window.isOpen()) {
		if (currentState->getNextState() != StateType::None) {
			StateType nextState = currentState->getNextState();
			currentState->resetNextState();
			switch (nextState) {
			case StateType::Timer:
				window.setSize(sf::Vector2u(230, 200));
				window.setView(sf::View(sf::FloatRect({ 0, 0 }, {230, 200})));
				timerstate.updateSettings(settingsstate.getSettings());
				currentState = &timerstate;
				break;
			case StateType::Settings:
				window.setSize(sf::Vector2u(230, 300));
				window.setView(sf::View(sf::FloatRect({ 0, 0 }, {230, 300})));
				currentState = &settingsstate;
				break;
			default:
				break;
			}
		}
		float dt = clock.restart().asSeconds();
		timerstate.updateTimer(dt);


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