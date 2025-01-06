#pragma once

/**
 * @file Auswahl.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-05-10
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "../Data/Data.h"
#include "../Einheiten/Battelion.h"
#include "../Einheiten/Einzelkampfer.h"

#include <iterator>

#include <memory>

/**
 * @brief Die Klasse sucht Einheiten mit bestimmten Kriterien und Bereitet sie
 * für die weitere Bearbeitung vor.
 * @todo Unterscheiden zwischen Battilion und Einzelkampfer
 */
class Auswahl
{
	public:
	Auswahl() = delete;

	/**
	 * @brief Construct a new Auswahl object
	 *
	 * @param data Eine Kopie des Data Pointers
	 */
	Auswahl(std::shared_ptr<Data>& data);
	~Auswahl();

	void sucheNachUnverletztenEinsetzbarenEinheiten();

	// Such Allgerhytmen
	/**
	 * @brief Sucht alle einheiten raus die Eingesetzt werden können.
	 *
	 */
	void sucheNachEinsetzbarenEinheiten();

	/**
	 * @brief Sucht alle Einsetzbaren und Unverletzen Einheiten raus.
	 *
	 */
	void sucheNachUnverletztenEinheiten();

	/**
	 * @brief Sucht alle Einsetzbaren und Verletzten(Hp < MAX_LEBEN)
	 * Einheiten raus.
	 *
	 */
	void sucheNachVerletzten();

	/**
	 * @brief Sucht alle Einsetzbaren Einheiten mit geringere
	 * Truppenmoral(Moral < MAX_MORAL) raus.
	 *
	 */
	void sucheNachTruppenmoral();

	/**
	 * @brief Sucht alle Einsetzbaren Einheiten raus die Starker sind als
	 * min raus.
	 *
	 * @param min Die Mindest Starke die eine Einheit haben muss.
	 */
	void sucheNachStarke(int min);

	/**
	 * @brief Leert das interne Objekt in dem die herausgesuchten einheiten
	 * gespeichert werden.
	 * @attention Die Funktion sollte vor jeder suche Aufgerufen werden! Die
	 * Einige Ausnahme ist das man nach mehreren Eigenschaften suchen will
	 * wie verlete und geringe Truppenmoral.
	 *
	 */
	void leeren();
	// Sortieren

	/**
	 * @brief Sortiert die herausgesuchten Einheiten nach der Starke.
	 *
	 * @param aufsteigend Bei false wird Absteigend(Starkste -> Schwachste)
	 * sortiert und bei true Aufsteigend(Schwachste -> Starkste).
	 */
	void sortiereNachStarke(bool aufsteigend);

	/**
	 * @brief Sortiert die herausgesuchten Einheiten nach der schwere der
	 * Verletzung.
	 *
	 * @param aufsteigend Bei false wird Absteigend(leicht Verletzt(99 HP)
	 * -> halb Tot (20 HP)) sortiert und bei true Aufsteigend(halb Tot (20
	 * HP) -> leicht Verletzt(99 HP)).
	 */
	void sortiereNachVerletzten(bool aufsteigend);

	/**
	 * @brief Sortiert die herausgesuchten Einheiten nach der Truppenmoral.
	 *
	 * @param aufsteigend Bei false wird Absteigend(Motiviertesten ->
	 * niedergeschlagen) sortiert und bei true Aufsteigend(niedergeschlagen
	 * -> Motiviertesten).
	 */
	void sortiereNachTruppenmoral(bool aufsteigend);

	/**
	 * @brief Get the Ausgewahlte Einheiten object
	 *
	 * @return std::vector<int> Gibt die Indexe der Einheiten zurück. Wenn
	 * man nach der Starke absteigen sortiert hat erhalt man mit
	 * getEinheit()[getAusgewahlteEinheiten()[1]]; die Starkste Einheit aus
	 * den Ausgesuchten Einheiten.
	 */
	std::vector<int> getAusgewahlteEinheiten()
	{
		return AusgewahlteEinheiten;
	}

	private:
	/**
	 * @brief Bei der suche nach mehreren Eigenschaften kann es dazu kommen
	 * das eine Einheit mehrfach ausgewahtl wird. Die Funktion erkennt die
	 * Dopplungen und entfernt Sie.
	 *
	 */
	void entferneDopplungen();

	/**
	 * @brief Der Vektor speichert die Einheiten die bei der suche
	 * Ausgewählt werden da sie das Suchkriterieum erfüllen.
	 *
	 */
	std::vector<int> AusgewahlteEinheiten;

	/**
	 * @brief Ein Kopie des Data Pointers mit dem auf die Einheiten und ihre
	 * Eigenschaften zugegriffen wird.
	 *
	 */
	std::shared_ptr<Data> DatenAuswahl;

	/**
	 * @brief Das Maximale Leben das eine Einheit haben kann ohne Effekte.
	 *
	 */
	const int MAX_LEBEN = 100;

	/**
	 * @brief Die Maximale Moral die eine Einheit haben kann.
	 *
	 */
	const int MAX_MORAL = 10;
};
