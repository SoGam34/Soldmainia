#include "Timer.h"

Timer::Timer()
{
	IDTimer.clear();
	EinzelTimer = 0;
}

void Timer::aktTimer()
{
	EinzelTimer--;
	for (auto& e : IDTimer)
	{
		e.second--;
	}
}

void Timer::neuerTimer(int dauer)
{
	EinzelTimer = dauer;
}

bool Timer::checkTimerAbgelaufen()
{
	return EinzelTimer == 0;
}

void Timer::neuerTimerMitID(int dauer, int id)
{
	IDTimer.push_back(std::make_pair(id, dauer));
}

bool Timer::checkTimerAbgelaufenMitID(int id)
{
	for (auto& i : IDTimer)
	{
		if (i.first == id)
		{
			if (i.second == 0)
			{
				return true;
			}
		}
	}
	return false;
}

int Timer::getTimerstand() const
{
	return EinzelTimer;
}

std::optional<int> Timer::getTimerstandMitID(int id) const
{
	for (size_t i = 0; i < IDTimer.size(); i++)
		if (IDTimer[i].first == id)
			return IDTimer[i].second;

	return {};
}
