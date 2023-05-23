#pragma once
#include "Data.h"

class Auswahl
{
public:
	Auswahl()=delete;
	Auswahl(std::shared_ptr<Data> data, std::mutex& mutex);
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
	std::shared_ptr<Data> myData;

	Button* cButtenLinks;
	Button* cButtenRechts;
	Button* cButtenUP;
	Button* cButtenDown;

};

