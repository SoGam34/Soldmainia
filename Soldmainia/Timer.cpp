#include "PreHeader.h"
#include "Timer.h"

Timer::Timer()
{
	vTimer.clear();
	iTimer = 0;
}

void Timer::aktTimer()
{
	iTimer--;
	for (auto e : vTimer)
		e.second--;
}

 void Timer::neuerTimer(int Dauer)
{
	iTimer = Dauer;
}

 bool Timer::checkTimerAbgelaufen()
{
	if (iTimer == 0)
		return true;
	return false;
}

 void Timer::neuerTimerMitID(int Dauer, int ID)
{
	vTimer.push_back(std::make_pair(ID, Dauer));
}

bool Timer::checkTimerAbgelaufenMitID(int ID)
{
	for (int i = 0; i < vTimer.size(); i++)
		if (vTimer[i].first == ID)
			if (vTimer[i].second == 0)
				return true;
	return false;
}

const int Timer::getTimerstand() const
{
	return iTimer;
}

const int Timer::getTimerstandMitID(int ID) const
{
	for (int i = 0; i < vTimer.size(); i++)
		if (vTimer[i].first == ID)
			return vTimer[i].second;
}
