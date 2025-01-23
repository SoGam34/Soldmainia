#include "Timer.h"

Timer::Timer() {
      IDTimer.clear();
      EinzelTimer = 0;
}

void Timer::aktTimer() {
      EinzelTimer--;
      if (EinzelTimer < 0) {
            EinzelTimer = 0;
      }
      for (auto& e : IDTimer) {
            e.second--;
            if (e.second < 0) {
                  e.second = 0;
            }
      }
}

void Timer::neuerTimer(int const dauer) {
      EinzelTimer = dauer;
}

bool Timer::checkTimerAbgelaufen() const {
      return EinzelTimer == 0;
}

void Timer::neuerTimerMitID(int const id, int const dauer) {
      IDTimer.push_back(std::make_pair(id, dauer));
}

bool Timer::checkTimerAbgelaufenMitID(int const id) {
      for (auto& i : IDTimer) {
            if (i.first == id) {
                  if (i.second == 0) {
                        return true;
                  }
            }
      }
      return false;
}

int Timer::getTimerstand() const {
      return EinzelTimer;
}

std::optional<int> Timer::getTimerstandMitID(int const id) const {
      for (const auto& i : IDTimer) {
            if (i.first == id) {
                  return i.second;
            }
      }

      return {};
}
