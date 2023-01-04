#pragma once
#include "Data.h"
#include <optional>

class Auswahl
{
public:
	Auswahl();
	Auswahl(Data* data);
	~Auswahl();

	// Erzeugen der Kacheln
	void AnzeigeVorbereitung();

	std::optional<std::string> updateAuswahl(sf::Vector2i MousPos);
	//Anzeigen
	void Mahlen(sf::RenderWindow& window);

	// Such Allgerhytmen
	void SucheNachEinsetzbarenEinheiten();

	void SucheNachVerletzten();

	void SucheNachTruppenmoral();

	void SucheNachStarke(int min);

	void SucheEinsetzbare_UND_GesundeEinheiten();

	// Sortieren
	void up();
	void SortiereNachStarke();
	void down();

	//Get/Set
	 std::string getEinheitsname(int ButtenID);

private:
	std::vector <Kachel*> vKacheln;
	std::vector <std::string> vAusgewahlteEinheiten;
	std::vector <std::pair<std::string, int>> vAusgewahlten;
	Data* myData;

	Butten* cButtenLinks;
	Butten* cButtenRechts;
	Butten* cButtenUP;
	Butten* cButtenDown;

};

