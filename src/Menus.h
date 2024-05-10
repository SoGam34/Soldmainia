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

/**
 * @brief Speichert in welchem Menu sich der Spieler gerade befindet
 * 
 */
enum Menus
{
	hauptmenu = 1,
	zentrale = 2,
	scoutbuero = 3,
	batillionsausbildungsstate = 4,
	traningszentrum = 5,
	auftraege = 6,
	aauftraege = 7,
	logistikSystem = 8,
	erholungsresort = 9,
	einzelMitglieder = 11,
	batillione = 12
};

/**
 * @brief Speichert die Aktuellen Upgrade Werte einer Einrichtung 
 * 
 */
struct GebaeudeUpgradeStats
{
	GebaeudeStats()
	{
		 BeschlaunigunsKosten = 100;
		 BeschlaunigungsFaktor = 0;

		 GebaudeSpezielleKosten = 100;
		 GebaudeSpezielleFaktor = 0;

		 AusführungsReduzierungsKosten = 100;
		 AusführungsReduzierungsFaktor = 0;
	}

	int BeschlaunigunsKosten;
	int BeschlaunigungsFaktor;

	int GebaudeSpezielleKosten;
	int GebaudeSpezielleFaktor;

	int AusführungsReduzierungsKosten;
	int AusführungsReduzierungsFaktor;
};

const int AUSWAHL_MENU_ZENTRALE = 1;
const int AUSWAHL_MENU_BATILIONAUSBILDUNGSZENTRUM = 2;
const int AUSWAHL_MENU_SCOUTBUERO = 3;
const int AUSWAHL_MENU_ERHOLUNGSRESORT = 4;
const int AUSWAHL_MENU_TRANINGSZENTRUM = 5;
const int AUSWAHL_MENU_VERFUEGBARE_AUFTRAGE = 6;
const int AUSWAHL_MENU_LAUFENDE_AUFTRAGE = 7;
const int AUSWAHL_MENU_LOGISTIK_SYSTEM = 8;
const int AUSWAHL_MENU_HAUPTMENU = 9;

const int AUSWAHL_AKTION_1 = 10;
const int AUSWAHL_AKTION_2 = 11;
const int AUSWAHL_AKTION_3 = 12;

const int AUSWAHL_UPGRADE_ZEIT = 13;
const int AUSWAHL_UPGRADE_SPEZIFISCH = 14;
const int AUSWAHL_UPGRADE_KOSTEN = 15;

const int AUSWAHL_SPEICHERN = 16;
const int AUSWAHL_BEENDEN = 17;
const int AUSWAHL_HILFE = 18;

