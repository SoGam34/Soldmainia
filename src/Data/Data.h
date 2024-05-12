#pragma once

/**
 * @file Data.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <vector>

#include "../Einheit.h"

/**
 * @brief Die Klasse speichert alle Informationen die von mehreren Klassen benötigt werden. 
 * 
 */
class Data
{
public:
	/**
	 * @brief Construct a new Data object
	 *
	 */
	Data();

	/**
	 * @brief Destroy the Data object
	 *
	 */
	~Data();

	/**
	 * @brief Get the Einheiten object
	 *
	 * @return std::vector<Einheit>& Alle Einheiten.
	 */
	std::vector<Einheit>& getEinheiten();

	/**
	 * @brief Hinzufügen einer neuen Einheit.
	 *
	 * @param e Die Einheit die hinzugefügt werden soll.
	 */
	void addEinheit(const Einheit &e);

	/**
	 * @brief Get the Bekanntheit object
	 *
	 * @return unsigned int Wie bekannt der Spieler aktuell ist.
	 */
	unsigned int getBekanntheit();

	/**
	 * @brief Set the Bekanntheit object
	 *
	 * @param value Die neue ablsolute Bekanntheit.
	 */
	void setBekanntheit(unsigned int value);

	/**
	 * @brief Get the Kontostand object
	 *
	 * @return int Das aktuelle Vermögen des Spielers.
	 */
	int getKontostand();

	/**
	 * @brief 'Überweisung' zum Spieler. Der Spieler erhalt Geld.
	 *
	 * @param betrag Der Betrag den der Spieler erhalt.
	 */
	void hinzufuegenZuKontostand(int betrag);

	/**
	 * @brief Es beginnt ein neuer Tag und der Zahler der die insgesamte Anzahl an Tagen Zahlt wird um eins erhöt.
	 *
	 */
	void erhoheAnzahlTage();

	/**
	 * @brief Get the Anzahl Tage object
	 *
	 * @return int Die Anzahl an Tagen die vergangen sind.
	 */
	int getAnzahlTage();

	/**
	 * @brief Get the Tages Dauer object
	 *
	 * @return float Wie lange ein Tag aktuell ist.
	 */
	float getTagesDauer();

	/**
	 * @brief Set the Tages Dauer object
	 *
	 * @param neueDauer Die neue lange eines Tages.
	 */
	void setTagesDauer(float neueDauer);

	/**
	 * @brief Gibt den Wert von MONATS_DAUER zurück.
	 *
	 * @return int Die Anzal an Tagen die ein Monat hat.
	 */
	int getMONATS_DAUER() const;

	/**
	 * @brief Speichert alle Daten in eine Speicherdatei.
	 *
	 * @warning Die Funktion ist noch nicht implementiert.
	 *
	 */
	void saveGameToFile();

private:

	/**
	 * @brief Speichert den Aktuellen Kontostand des Spielers.
	 * 
	 */
	int Kontostand = 1000000000;

	/**
	 * @brief Die Anzalhl an Tagen die im gesamten Spiel vergangen sind. 
	 * 
	 */
	int AnzahlTage = 0;

	/**
	 * @brief Wie lange ein Tag in der Echten Welt dauert. 
	 * 
	 */
	float TagesDauer = 1.2;

	/**
	 * @brief Die Dauer eines Monats.
	 * 
	 */
	const int MONATS_DAUER = 30;

	/**
	 * @brief Wie bekannt ein Spieler im spiel ist.
	 * 
	 */
	unsigned int Bekantheit = 0;

	/**
	 * @brief Ein Vector der alle Einheiten des Spielers speichert. 
	 * 
	 */
	std::vector<Einheit> Einheiten;
};
