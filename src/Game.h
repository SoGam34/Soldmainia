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

#include "Gebaude/Batilion_Ausbildungszentrum.h"
#include "Gebaude/Erholungsresort.h"
#include "Gebaude/Scoutbuero.h"
#include "Gebaude/Traningszentrum.h"
#include "Gebaude/Zentrale.h"

#include "Rendern/View.h"

#include "Data/Data.h"

#include "Menus.h"
#include "Rendern/Auswahl.h"

#include <chrono>
#include <memory>

#include <spdlog/formatter.h>
#include <spdlog/logger.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/stopwatch.h>

/**
 * @brief Die Klasse verwaltet alles generelles und koordiniert die alle anderen
 * Klassen.
 *
 */
class Game
{
	public:
	/**
	 * @brief Construct a new Game object
	 *
	 */
	Game();

	/**
	 * @brief Destroy the Game object
	 *
	 */
	~Game();

	/**
	 * @brief Eine Funktion die solange ausgeführt wird bis das Spiel vorbei
	 * ist. Die Funktion triggert allmöglichen anderen Events und ist der
	 * Kern des Spiels.
	 *
	 */
	void spielLauft();

	private:
	/**
	 * @brief Die neuste User eingabe wird überprüft. Bei Input wird die
	 * dazugehorige Aktion ausgefürt.
	 *
	 */
	void update();

	/**
	 * @brief Die Ingame Zeit wird aktualliesert und alles was davon
	 * abhangig ist.
	 *
	 */
	void zeit();

	/**
	 * @brief Speichert das Aktuelle Menu in dem sich der Spieler befindet.
	 *
	 */
	Menus AktuellesMenu;

	/**
	 * @brief Speichert die Upgrade Informationen des Akteuellen Gebaudes.
	 *
	 */
	GebaeudeUpgradeStats Stats;

	InProgressStats Progress;

	/**
	 * @brief Speichert wann der letzte ingame Tag begonnen hat, damit die
	 * Tage alle gleichlang und FPS unabhängig sind.
	 *
	 */
	std::chrono::time_point<std::chrono::steady_clock>
	    ZeitpunktDesLetztenTages;

	std::shared_ptr<spdlog::logger> log;

	std::unique_ptr<View> view;

	std::shared_ptr<Data> Daten;

	Batillion_Ausbildungszentrum* BAZ;

	Scoutbuero* Scoutbueros;

	Traningszentrum* Traningzentren;

	Zentrale* Hauptquatier;

	Erholungsresort* Erholungsresorts;
};
