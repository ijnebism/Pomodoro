#include "SettingsData.hpp"
#include <fstream>
#include <sstream>

void SettingsData::loadFromFile() {
	std::ifstream file(filename);
	if (!file.is_open()) {
		return;
	}
	std::string line;
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::string key;
		if (std::getline(iss, key, '=')) {
			std::string value;
			if (std::getline(iss, value)) {
				if (key == "workDuration") workDuration = std::stoi(value);
				else if (key == "breakDuration") breakDuration = std::stoi(value);
				else if (key == "autoStartWork") autoStartWork = (value == "1");
				else if (key == "autoStartBreak") autoStartBreak = (value == "1");
				else if (key == "audioVolume") audioVolume = std::stof(value);
			}
		}
	}
}

void  SettingsData::saveToFile() const {
	std::ofstream file(filename);
	if (!file.is_open()) {
		return;
	}
	file << "workDuration=" << workDuration << "\n";
	file << "breakDuration=" << breakDuration << "\n";
	file << "autoStartWork=" << (autoStartWork ? "1" : "0") << "\n";
	file << "autoStartBreak=" << (autoStartBreak ? "1" : "0") << "\n";
	file << "audioVolume=" << audioVolume << "\n";
}