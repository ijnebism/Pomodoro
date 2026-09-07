#include "Timer.hpp"
#include <iostream>

Timer::Timer(const sf::Font& font, const sf::Texture& clockTexture, const sf::Texture& settingsTexture, const sf::Texture& hideTexture, const sf::Texture& moveTexture, const SettingsData& settingsData, const sf::Texture& startTexture, const sf::Texture& resetTexture, const sf::Sound& alarmSound) :
time(font),
status(font),
settingsButton(sf::Vector2f({125,5}), settingsTexture, sf::Color(128,128,128), sf::Color(90, 90, 90), sf::Color::Green),
timerButton(sf::Vector2f({ 25,5 }), clockTexture, sf::Color(128,128,128), sf::Color(90, 90, 90), sf::Color::Green),
hideButton(sf::Vector2f({175,5 }), hideTexture, sf::Color(128,128,128), sf::Color(90, 90, 90), sf::Color::Green),
moveButton(sf::Vector2f({ 75,5 }), moveTexture, sf::Color(128,128,128), sf::Color(90, 90, 90), sf::Color::Green),
startButton(sf::Vector2f({ 75,110 }), startTexture, sf::Color(128,128,128), sf::Color(90, 90, 90), sf::Color::Green),
resetButton(sf::Vector2f({ 125,110 }), resetTexture, sf::Color(128,128,128), sf::Color(90, 90, 90), sf::Color::Green),
settingsData(settingsData),
alarmSound(alarmSound)
{

	secondsRemaining = settingsData.workDuration * 60;
	time.setString(std::to_string(secondsRemaining / 60) + ":" +
		(secondsRemaining % 60 < 10 ? "0" : "") + std::to_string(secondsRemaining % 60));
	time.setCharacterSize(48);
	time.setOutlineColor(sf::Color::Black);
	time.setOutlineThickness(2);
	time.setFillColor(sf::Color::White);

	timerButton.setActive(true);

	status.setString("Pomodoro");
	status.setCharacterSize(16);
	status.setOutlineColor(sf::Color::Black);
	status.setOutlineThickness(1);
	status.setFillColor(sf::Color::White);
	
}

void Timer::handleInput(sf::RenderWindow& window) {
	while (const std::optional event = window.pollEvent()) {
		if (event->is<sf::Event::Closed>()) {
			window.close();
		}

		sf::Vector2i mousePos = sf::Mouse::getPosition(window);

		if (settingsButton.isClicked(mousePos, sf::Mouse::Button::Left, *event)) {
			nextState = StateType::Settings;

		}
		if (hideButton.isClicked(mousePos, sf::Mouse::Button::Left, *event)) {
			hideButton.toggleActive();
		}
		if (startButton.isClicked(mousePos, sf::Mouse::Button::Left, *event)) {
			startButton.toggleActive();
		}
		if (resetButton.isClicked(mousePos, sf::Mouse::Button::Left, *event)) {
			resetState();
		}
	}
}

void Timer::update(float dt, sf::RenderWindow& window) {
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	settingsButton.updateHover(mousePos);
	timerButton.updateHover(mousePos);
	hideButton.updateHover(mousePos);
	moveButton.updateHover(mousePos);
	startButton.updateHover(mousePos);
	resetButton.updateHover(mousePos);

	moveButton.updatePressed(mousePos);

	if (moveButton.getActive()) {
		sf::Vector2i currentScreenPos = sf::Mouse::getPosition();
		if (!wasDragging) {
			dragStartScreenPos = currentScreenPos;
			dragStartWindowPos = window.getPosition();
			wasDragging = true;
		}
		else {
			sf::Vector2i delta = currentScreenPos - dragStartScreenPos;
			window.setPosition(dragStartWindowPos + delta);
		}
	}
	else {
		wasDragging = false;
	}
}

void Timer::resetState() {
	startButton.setActive(false);
	secondsRemaining = settingsData.workDuration * 60;
	currentPhase = TimerPhase::Work;
	status.setString("Work");
	time.setString(std::to_string(secondsRemaining / 60) + ":" +
		(secondsRemaining % 60 < 10 ? "0" : "") + std::to_string(secondsRemaining % 60));
}

void Timer::updateTimer(float dt) {
	if (!startButton.getActive()) {
		return;
	}

	accumulatedTime += dt;
	if (accumulatedTime >= 1.f) {
		accumulatedTime -= 1.f;
		secondsRemaining -= 1;
		time.setString(std::to_string(secondsRemaining / 60) + ":" +
			(secondsRemaining % 60 < 10 ? "0" : "") + std::to_string(secondsRemaining % 60));
		if (secondsRemaining <= 0) {
			alarmSound.setVolume(settingsData.audioVolume);
			alarmSound.play();
			switchPhase();
			if (settingsData.autoStartWork && currentPhase == TimerPhase::Work) {
				startButton.setActive(true);
			}
			else if (settingsData.autoStartBreak && currentPhase == TimerPhase::Break) {
				startButton.setActive(true);
			}
			else {
				startButton.setActive(false);
			}
		}
	}
}

void Timer::updateSettings(const SettingsData& newSettings) {
	settingsData.workDuration = newSettings.workDuration;
	settingsData.breakDuration = newSettings.breakDuration;
	settingsData.autoStartWork = newSettings.autoStartWork;
	settingsData.autoStartBreak = newSettings.autoStartBreak;
	settingsData.audioVolume = newSettings.audioVolume;
}

void Timer::switchPhase() {
	if (currentPhase == TimerPhase::Work) {
		currentPhase = TimerPhase::Break;
		secondsRemaining = settingsData.breakDuration * 60;
		status.setString("Break");
	}
	else if (currentPhase == TimerPhase::Break) {
		currentPhase = TimerPhase::Work;
		secondsRemaining = settingsData.workDuration * 60;
		status.setString("Pomodoro");
	}
	time.setString(std::to_string(secondsRemaining / 60) + ":" +
		(secondsRemaining % 60 < 10 ? "0" : "") + std::to_string(secondsRemaining % 60));
}

void Timer::render(sf::RenderWindow& window) {
	sf::Vector2u windowSize = window.getSize();
	window.clear(sf::Color::Transparent);


	if (!hideButton.getActive()) {

		time.setOrigin({ time.getLocalBounds().size.x / 2.f, time.getLocalBounds().size.y / 2.f });
		status.setOrigin({ status.getLocalBounds().size.x / 2.f, status.getLocalBounds().size.y / 2.f });
		time.setPosition({windowSize.x / 2.f, 70});
		status.setPosition({windowSize.x / 2.f, 48});
		window.draw(time);
		window.draw(status);
		settingsButton.render(window);
		timerButton.render(window);
		moveButton.render(window);
		startButton.render(window);
		resetButton.render(window);

	}
	
	hideButton.render(window);
	window.display();
}

bool Timer::isMouseOverUI(const sf::Vector2i& mousePos) const {
	if (hideButton.getActive()) {
		return hideButton.isHovered();
	}
	return settingsButton.isHovered() || timerButton.isHovered() || hideButton.isHovered() || moveButton.isHovered() || startButton.isHovered() || resetButton.isHovered();
}