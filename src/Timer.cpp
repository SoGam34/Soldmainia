#include "PreHeader.h"
#include "Timer.h"

Timer::Timer()
{
	IDTimer.clear();
	EinzelTimer = 0;
}

void Timer::aktTimer()
{
	EinzelTimer--;
	for (auto e : IDTimer)
		e.second--;
}

 void Timer::neuerTimer(int Dauer)
{
	 EinzelTimer = Dauer;
}

 bool Timer::checkTimerAbgelaufen()
{
	if (EinzelTimer == 0)
		return true;
	return false;
}

 void Timer::neuerTimerMitID(int Dauer, int ID)
{
	IDTimer.push_back(std::make_pair(ID, Dauer));
}

bool Timer::checkTimerAbgelaufenMitID(int ID)
{
	for (int i = 0; i < IDTimer.size(); i++)
		if (IDTimer[i].first == ID)
			if (IDTimer[i].second == 0)
				return true;
	return false;
}

const int Timer::getTimerstand() const
{
	return EinzelTimer;
}

const int Timer::getTimerstandMitID(int ID) const
{
	for (int i = 0; i < IDTimer.size(); i++)
		if (IDTimer[i].first == ID)
			return IDTimer[i].second;
}
