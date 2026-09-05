#pragma once
#include <string>

class SettingsData {
public:
	int workDuration = 50; 
	int breakDuration = 10; 
	bool autoStartWork = false;
	bool autoStartBreak = false;
	float audioVolume = 100.0f; 
	void loadFromFile();
	void saveToFile() const;

private:
	const std::string filename = "config.txt";
};