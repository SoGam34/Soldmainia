#pragma once
#include "Data.h"
#include <optional>
#include <memory>

class Auswahl
{
public:
	Auswahl()=delete;
	Auswahl(Data* data);
	~Auswahl();

	// Erzeugen der Kacheln
	void AnzeigeVorbereitung();

	std::optional<int> updateAuswahl(sf::Vector2i MousPos);
	//Anzeigen
	void Mahlen(sf::RenderWindow& window);

	// Such Allgerhytmen
	void SucheNachEinsetzbarenEinheiten();

	void SucheNachVerletzten();

	void SucheNachTruppenmoral();

	void SucheNachStarke(int min);

	void SucheEinsetzbare_UND_GesundeEinheiten();

	void leeren();
	// Sortieren
	void up();
	void SortiereNachStarke();
	void down();

private:
	std::vector <std::unique_ptr<Kachel>> vKacheln;
	std::vector <int> vAusgewahlteEinheiten;
	Data* myData;

	Butten* cButtenLinks;
	Butten* cButtenRechts;
	Butten* cButtenUP;
	Butten* cButtenDown;

};

