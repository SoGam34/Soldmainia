#pragma once

class Timer
{
public:

	Timer();
	//Allgemeine Timer Funktione
	void aktTimer();

	//einzelTimer Funktion
	void neuerTimer(int dauer);
	bool checkTimerAbgelaufen();

	// Timer mit Id
	void neuerTimerMitID(int dauer, int id);
	bool checkTimerAbgelaufenMitID(int id);

	//Get/set Funktionen
	const int getTimerstand() const;
	const int getTimerstandMitID(int id) const;

private:
	int EinzelTimer; // Einzel
	std::vector<std::pair<int, int>> IDTimer; // ID Timer
};

