#include "Settings.hpp"
#include <iostream>

Settings::Settings(const sf::Font& font, const sf::Texture& clockTexture, const sf::Texture& settingsTexture, const sf::Texture& hideTexture, const sf::Texture& moveTexture, const SettingsData& settingsData) :
	settingsButton(sf::Vector2f({ 125,5 }), settingsTexture, sf::Color(128, 128, 128), sf::Color(90, 90, 90), sf::Color::Green),
	timerButton(sf::Vector2f({ 25,5 }), clockTexture, sf::Color(128, 128, 128), sf::Color(90, 90, 90), sf::Color::Green),
	hideButton(sf::Vector2f({ 175,5 }), hideTexture, sf::Color(128, 128, 128), sf::Color(90, 90, 90), sf::Color::Green),
	moveButton(sf::Vector2f({ 75,5 }), moveTexture, sf::Color(128, 128, 128), sf::Color(90, 90, 90), sf::Color::Green),
	workduration(font, sf::Vector2f({ 150, 50 }), sf::Vector2f({ 50, 30 })),
	breakduration(font, sf::Vector2f({ 150, 85 }), sf::Vector2f({ 50, 30 })),
	workLabel(font),
	breakLabel(font),
	workToggle(sf::Vector2f({ 170, 130 }), sf::Color::Red, sf::Color(200, 60, 60), sf::Color::Green),
	breakToggle(sf::Vector2f({ 170, 165 }), sf::Color::Red, sf::Color(200, 60, 60), sf::Color::Green),
	workToggleLabel(font),
	breakToggleLabel(font),
	audioLabel(font),
	volumeLabel(font),
	audioSlider(sf::Vector2f({ 30, 230 }), sf::Vector2f({ 110, 14 }), 0.f, 100.f, 100.f),
	settingsData(settingsData)
{
	settingsButton.setActive(true);

	workLabel.setString("Work  (min)");
	workLabel.setCharacterSize(16);
	workLabel.setFillColor(sf::Color::White);
	workLabel.setOutlineColor(sf::Color::Black);
	workLabel.setOutlineThickness(1);
	workLabel.setPosition({26, 54});


	breakLabel.setString("Break (min)");
	breakLabel.setCharacterSize(16);
	breakLabel.setFillColor(sf::Color::White);
	breakLabel.setOutlineColor(sf::Color::Black);
	breakLabel.setOutlineThickness(1);
	breakLabel.setPosition({ 26, 89 });

	workToggleLabel.setString("AutoStart  Work");
	workToggleLabel.setCharacterSize(16);
	workToggleLabel.setFillColor(sf::Color::White);
	workToggleLabel.setOutlineColor(sf::Color::Black);
	workToggleLabel.setOutlineThickness(1);
	workToggleLabel.setPosition({ 26, 134 });

	breakToggleLabel.setString("AutoStart Break");
	breakToggleLabel.setCharacterSize(16);
	breakToggleLabel.setFillColor(sf::Color::White);
	breakToggleLabel.setOutlineColor(sf::Color::Black);
	breakToggleLabel.setOutlineThickness(1);
	breakToggleLabel.setPosition({ 26, 169 });

	audioLabel.setString("Audio Volume");
	audioLabel.setCharacterSize(16);
	audioLabel.setFillColor(sf::Color::White);
	audioLabel.setOutlineColor(sf::Color::Black);
	audioLabel.setOutlineThickness(1);
	audioLabel.setPosition({ 26, 200 });

	volumeLabel.setString("100%");
	volumeLabel.setCharacterSize(16);
	volumeLabel.setFillColor(sf::Color::White);
	volumeLabel.setOutlineColor(sf::Color::Black);
	volumeLabel.setOutlineThickness(1);
	volumeLabel.setPosition({ 150, 223 });

	workduration.setValue(settingsData.workDuration);
	breakduration.setValue(settingsData.breakDuration);
	workToggle.setActive(settingsData.autoStartWork);
	breakToggle.setActive(settingsData.autoStartBreak);
	audioSlider.setValue(settingsData.audioVolume);
}

void Settings::handleInput(sf::RenderWindow& window) {
	while (const std::optional event = window.pollEvent()) {
		if (event->is<sf::Event::Closed>()) {
			window.close();
		}
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		if (timerButton.isClicked(mousePos, sf::Mouse::Button::Left, *event)) {
			nextState = StateType::Timer;
		}
		if (hideButton.isClicked(mousePos, sf::Mouse::Button::Left, *event)) {
			hideButton.toggleActive();
		}

		if (breakToggle.isClicked(mousePos, sf::Mouse::Button::Left, *event)) {
			breakToggle.toggleActive();
		}
		if (workToggle.isClicked(mousePos, sf::Mouse::Button::Left, *event)) {
			workToggle.toggleActive();
		}

		workduration.handleInput(*event, window);
		breakduration.handleInput(*event, window);
		audioSlider.handleInput(*event, window);

	}
}

void Settings::update(float dt, sf::RenderWindow& window) {
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	settingsButton.updateHover(mousePos);
	timerButton.updateHover(mousePos);
	hideButton.updateHover(mousePos);
	moveButton.updateHover(mousePos);
	workToggle.updateHover(mousePos);
	breakToggle.updateHover(mousePos);
	audioSlider.update(mousePos);
	
	moveButton.updatePressed(mousePos);
	volumeLabel.setString(std::to_string(static_cast<int>(audioSlider.getValue())) + "%");

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

	settingsData.workDuration = workduration.getValue();
	settingsData.breakDuration = breakduration.getValue();
	settingsData.autoStartWork = workToggle.getActive();
	settingsData.autoStartBreak = breakToggle.getActive();
	settingsData.audioVolume = audioSlider.getValue();
	settingsData.saveToFile();
}

void Settings::render(sf::RenderWindow& window) {
	sf::Vector2u windowSize = window.getSize();
	window.clear(sf::Color::Transparent);

	if (!hideButton.getActive()) {
		settingsButton.render(window);
		timerButton.render(window);
		moveButton.render(window);
		workduration.render(window);
		breakduration.render(window);
		window.draw(workLabel);
		window.draw(breakLabel);
		window.draw(workToggleLabel);
		window.draw(breakToggleLabel);
		workToggle.render(window);
		breakToggle.render(window);
		window.draw(workToggleLabel);
		window.draw(breakToggleLabel);
		window.draw(audioLabel);
		window.draw(volumeLabel);
		audioSlider.render(window);
	}

	hideButton.render(window);
	window.display();
}

bool Settings::isMouseOverUI(const sf::Vector2i& mousePos) const {
	return settingsButton.isHovered() || timerButton.isHovered() || hideButton.isHovered() || moveButton.isHovered() || 
		workduration.isHovered(mousePos) || breakduration.isHovered(mousePos) || workToggle.isHovered() || breakToggle.isHovered() ||
		audioSlider.isHovered(mousePos);
}