#pragma once
#include "Data/Data.h"
#include "Einheit.h"

#include <iterator> // for iterators

#include <memory>

class Auswahl
{
public:
	Auswahl() = delete;
	Auswahl(std::shared_ptr<Data> data);
	~Auswahl();

	// Such Allgerhytmen
	void sucheNachEinsetzbarenEinheiten();

	void sucheNachVerletzten();

	void sucheNachTruppenmoral();

	void sucheNachStarke(int min);

	void leeren();
	// Sortieren
	void sortiereNachStarke(bool aufsteigend); //TODO Upgrade: Auf- und Absteigend sortieren

	void sortiereNachVerletzten(bool aufsteigend); //TODO Upgrade: Auf- und Absteigend sortieren

	void sortiereNachTruppenmoral(bool aufsteigend); //TODO Upgrade: Auf- und Absteigend sortieren

private:

	void entferneDopplungen();

	std::vector<int> AusgewahlteEinheiten;
	std::shared_ptr<Data> Daten;

	const int MAX_LEBEN = 100;
	const int MAX_MORAL = 10;

};

