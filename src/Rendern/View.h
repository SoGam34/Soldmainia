#pragma once

/**
 * @file View.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "../Data/Data.h"
#include "../Menus.h"
#include "Auswahl.h"

#include <iostream>
#include <memory>
#include <vector>

/**
 * @brief Die Klasse zeigt dem Spieler alles an und leitet die eingabe an Game weiter. 
 * 
 */
class View: public Auswahl
{
public:
	//De/Konstrucktor
	View() = delete;

	/**
	 * @brief Construct a new View object
	 * 
	 * @param data Eine Kopie des Data Pointers. 
	 */
	View(std::shared_ptr<Data> data);

	/**
	 * @brief Destroy the View object
	 * 
	 */
	~View();

	/**
	 * @brief Die Funktion gibt an ob der Spieler das Spiel beendet hat oder nicht.
	 *
	 * @return true Das Spieler will weiter Spielen.
	 * @return false Der Spieler will das Spiel beenden.
	 */
	bool getSpielIstAktiv();

	/**
	 * @brief Get the Eingabe object
	 *
	 * @return int Die eingabe des Spielers

	 * @attention Die Funktion gibt die Eingabe vom Spieler dierekt wieder **ohne** auf irgendwas zu prüfen. Das selbständige Prüfen ist daher essentiel.
	 * @link ungueltigeEingabe() @endlink
	 */
	int getLetzteNutzerEingabe();

	/**
	 * @brief Die Funktion rendert das Spiel.
	 *
	 * @param aktuellesMenu Das Menu in dem Sich der Spieler grade befindet.
	 * @param stats Die Upgrade informationen des Gebaudes in dem der Spieler sich gerade befindet.
	 */
	void ausgabe(Menus aktuellesMenu, GebaeudeUpgradeStats stats);

	/**
	 * @brief Ein Interaktives Sondermenu bei dem der Spieler eine Einheit für den Aufrufer aussucht.
	 *
	 * @param verwendugszweck Für was wird die Einheit ausgewählt. 
	 
	 * @return int Der Index der Einheit. Mögliche Verwendung 
	 * 	 @code {.cpp}
	 *   Data::getEinheiten()[View::dialogAuswahlEinheit("Auswahl für ...")]
	 *   @endcode
	 *   gibt die vom Spieler gewählte Einheit zurück.
	 */
	int dialogAuswahlEinheit(std::string verwendungszweck);

	/**
	 * @brief Die Eingabe ist nicht richtig und kann keiner Aktion zugeordnet werden.
	 *
	 */
	void ungueltigeEingabe();

	/**
	 * @brief Starten einer neuen Benarichtigung. Lauft bereits eine Benarichtigung werden beide Gleichzeitig angezeigt.
	 * @warning Die Funktion ist noch nicht implementiert. 
	 * 
	 * @param benarichtigungsText Der Text der Angezeigt werden soll.
	 * @param benarichtigungsArt Die Art der Benarichtigung. 
	 * @param gutfuerSpieler Bringt das Ereigniss den Spieler voran oder nicht, z. B. ist der Auftrag erfolgreich Abgeschlossen oder gescheitert. 
	 */
	void addBenarichtigung(std::string benarichtigungsText,
			int benarichtigungsArt, bool gutfuerSpieler);

private:

	/**
	 * @brief Wenn der Spieler weitere Informationen oder hilfe bei der bedinung braucht vergleichbar mit --help. Interaktiv gestaltet.
	 * @warning Die Funktion ist noch nicht implementiert. 
	 *
	 */
	void dialogHilfe();

	/**
	 * @brief Gibt die Kopfzeile mit allgemeinen Informationen aus.
	 *
	 * @param titel Das Menu in dem sich der Spieler befindetet.
	 */
	void printKopfZeile(std::string titel);

	/**
	 * @brief Die Funktion Kummert sich um alle Benarichtigungen an den Spieler.
	 *
	 */
	void printBenarichtigung();

	/**
	 * @brief Die Letzte Zeile bevor der Spieler wieder was eingeben kann.
	 *
	 */
	void printFussZeile();

	/**
	 * @brief Gibt die Upgrade Informationen eines Gebaudes aus.
	 *
	 * @param stats Die genauen Zahlen zu den einzelnen Upgrades
	 * @param zeitText  Der Text der beim Zeit Upgrade angezeigt werden soll.
	 * @param spzifischText Der Text der beim Gebaeude spzifischen Upgrade angezeigt werden soll.
	 * @param kostenText Der Text der beim Kosten Upgrade angezeigt werden soll.
	 */
	void printGebaeudeStats(GebaeudeUpgradeStats stats, std::string zeitText,
			std::string spzifischText, std::string kostenText);

	/**
	 * @brief Das Aktuelle Menu in dem sich der Spieler befindet.
	 *
	 */
	Menus ZuRenderndesMenu;

	/**
	 * @brief Die letzte Eingabe des Spielers.
	 *
	 */
	int Eingabe;

	/**
	 * @brief Speichert alle Relevanten Informationen die zum Anzeigen einer Benarichtigung benötigt werden.
	 * @details Der String speichert den Anzuzeigenden Text, der int die Art der Benarichtigung und der bool ob diese Gut für den Spieler ist.
	 *
	 */
	std::vector<std::string, std::pair<int, bool>> Benarichtigungen;

	/**
	 * @brief Eine Kopie des Data Pointers.
	 *
	 */
	std::shared_ptr<Data> Daten;
};
