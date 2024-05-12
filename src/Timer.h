#pragma once

/**
 * @file Timer.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <optional>
#include <vector>

/**
 * @brief Eine Klasse die sich um die Zeitverwaltung kummert
 * 
 */
class Timer
{
public:
	/**
	 * @brief Construct a new Timer object
	 * 
	 */
	Timer();

	/**
	 * @brief Aktualisieren aller aktiven Timer, dabei werden die Timer um eins nach unten gezahlt 
	 * 
	 */
	void aktTimer();

	/**
	 * @brief Startet einen neuen Timer. Lauft bereits ein EinzelTimer wird er überschrieben
	 * 
	 * @param dauer Die Zeit in Tagen die der Timer laufen soll.
	 */
	void neuerTimer(int dauer);

	/**
	 * @brief Überprüft ob die zu wartene Zeit, von dem EinzelTimer, um ist.
	 * 
	 * @return true Die Zeit ist um der Timer = 0
	 * @return false Der Timer lauft noch oder er ist bereits vor mindestens einem Tag abgelaufen (Timer < 0)
	 */
	bool checkTimerAbgelaufen();

	/**
	 * @brief Legt einen neuen Timer an der unabhangig von anderen ist und andere nicht in die Quere kommt. Wenn diese Funktion verwendet wird können mehrere Timer gleichzeitig laufen. 
	 * 
	 * @param dauer Die Zeit in Tagen die der Timer laufen soll.
	 * @param id Die Timer Nummer bzw Name mit der der Timer bei der überprüfung identifiziert werden kann.
	 */
	void neuerTimerMitID(int id, int dauer);

	/**
	 * @brief Überprüft ob die zu wartene Zeit, von dem angegebenen Timer, um ist.
	 * 
	 * @param id Die Timer Nummer bzw Name des zu überprüfenden Timers
	 * @return true Die Zeit ist um der Timer = 0
	 * @return false Der Timer lauft noch, er ist bereits vor mindestens einem Tag abgelaufen (Timer < 0) oder es wurde kein Timer mit der angegebenen ID gefunden.
	 */
	bool checkTimerAbgelaufenMitID(int id);

	/**
	 * @brief Get the Timerstand object
	 * 
	 * @return int Die Anzahl an Tagen bis der Timer abglaufen ist.
	 */
	int getTimerstand() const;

	/**
	 * @brief Get the Timerstand Mit id object
	 * 
	 * @param id Die Timer Nummer bzw Name des zu überprüfenden Timers
	 * @return std::optional<int> Die Anzahl an Tagen bis der Timer mit der zugehörigen id abglaufen ist oder {} wenn kein timer mit der angegebenen id gefunden wurde. 
	 */
	std::optional<int> getTimerstandMitID(int id) const;

private:

	/**
	 * @brief Ein einzelner Timer 
	 * 
	 */
	int EinzelTimer;

	/**
	 * @brief Eine Sammlung von mehreren Timern. Die mit einer ID und der noch verbleibenden Zeit gespeichert werden. 
	 * 
	 */
	std::vector<std::pair<int, int>> IDTimer;
};

