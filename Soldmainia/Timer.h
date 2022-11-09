#pragma once
#include <vector>

class Timer
{
public:

	Timer();
	//Allgemeine Timer Funktione
	void aktTimer();

	//einzelTimer Funktion
	 void neuerTimer(int Dauer);
	 bool checkTimerAbgelaufen();

	// Timer mit Id
	 void neuerTimerMitID(int Dauer, int ID);
	bool checkTimerAbgelaufenMitID(int ID);

	//Get/set Funktionen
	 int getTimerstand();
	 int getTimerstandMitID(int ID);

private:
	int iTimer; // Einzel
    std::vector <std::pair<int,int>> vTimer; // ID Timer
};

