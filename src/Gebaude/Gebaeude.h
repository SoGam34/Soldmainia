#pragma once

#include "../Data/Data.h"
#include "../Timer.h"

#include <memory>

class Gebaeude: public Timer
{
public:
	//--------------------------------Konstruktoren----------------------------------------------//
	Gebaeude() = delete;

	//Konstrucktor mit allen informationen fuer eine vollstandige Initzialisierung 
	Gebaeude(std::shared_ptr<Data> data, unsigned short int KostenFaktor,
			unsigned short int ZeitFaktor);
	virtual ~Gebaeude();

	//--------------------------------Aufgaben Ablauf----------------------------------------------//

	/*
	 Name: GebaeudeAusfuhrungskosten
	 param: keine
	 Aufgabe: Die virtuelle Funktion berechnet wie viel die Ausfuhrung kostet
	 Retrun: Die Funktion gibt die kosten als int zurueck
	 */
	virtual unsigned const int getGebaeudeAusfuhrungskosten() const = 0;

	/*
	 Name: BeginnAufgabe
	 param: keine
	 Aufgabe: Die Funktion beginnt die Aufgabe des Gebaudes z.b. beim BAZ der start der Ausbildung
	 Retrun: keine
	 */
	void beginneAufgabe();

	/*
	 Name: aktualisierenProzessZustand
	 param: keine
	 Aufgabe: Die Funktion aktualisiert den Text der Kachel mit dem GebaudeAktivText
	 Retrun: kein
	 */
	inline void aktualisierenProzessZustand();

	/*
	 Name: GebaudeAktivText
	 param: keine
	 Aufgabe: Die virtuelle Funktion erstellt den Text der Angezeigt wird wenn das Gebaude aktiv ist
	 Retrun: Die Funktion gibt den Text als stringstram zurueck
	 */
	virtual const std::stringstream getGebaudeAktivText() const = 0;

	/*
	 Name: BeendenDerAusfuhrung
	 param: keine
	 Aufgabe: Die virtuelle Funktion sorgt fuer ein geregeltes Ende der Ausfuhrung
	 Retrun: keine
	 */
	virtual void beendenDerAusfuhrung() = 0;

	//--------------------------------Upgraden des Gebaeudes----------------------------------------------//

	/*
	 Name: BeschleunigungDerAufgabenDurchfuehrung
	 param: keine
	 Aufgabe: Die Funktion modifiziert den iAufgabenDurchfuehrungZeitFaktor so das die Durchfuerung Schneller ist und passt den Kontostand sowie die Kacheln an
	 Retrun: kein
	 */
	void beschleunigungDerAufgabenDurchfuehrung();

	/*
	 Name: ReduzierenDerAusfuhrungsKosten
	 param: keine
	 Aufgabe: Die Funktion modifiziert den iAusfuhrungsKostenFaktor so das die Durchfuerung der Aufgabe gunstiger ist und passt den Kontostand sowie die Kacheln an
	 Retrun: kein
	 */
	void reduzierenDerAusfuhrungsKosten();

	//--------------------------------Allgemeine Funktionen Gebaeudes----------------------------------------------//

	/*
	 Name: aktualisierenInformationsText
	 param: keine
	 Aufgabe: Die virtuelle Funktion aktualisiert den Informationstext sodass der Spieler weis was die Aufgabe des gebaudes ist und unter welchen Bedingungen diese Erfullt wird
	 Retrun: kein
	 */
	virtual inline void aktualisierenInformationsText() = 0;

	/*
	 Name: aktualisierenInformationsText
	 param: keine
	 Aufgabe: Die Funktion ermittelt die Zeit die Vorausichtlich fuer die ausfuehrung der Aufgabe gebraucht wird unter Berucksichtigung von den folgenden Faktoren, des iZeitversatz, des iZeitFaktor, des iGeschwindikeitsFaktor und der Bekanntheit
	 Retrun: kein
	 */
	void berrechnungVoraussichtlicheZeit();

	/*
	 Name: aktualisierenTimer
	 param: keine
	 Aufgabe: Die Funktion aktualisiert den Timer und ruft bei Ablauf BeendenDerAusfuhrung auf und wenn der Timer am Ablaufen ist dann wird aktualisierenProzessZustand aufgerufen
	 Retrun: kein
	 */
	void aktualisierenTimer();

	// Daten zeiger
	std::shared_ptr<Data> Daten;

	// Wenn true dann wird die Aufgabe Ausgefuhrt der Prozess ist am laufen/aktiv	
	bool ProzessAktiv;

	// Gibt an wie lange die Ausbildung vorausichtlich dauert 				
	unsigned short int VoraussichtlicheZeit;

	// Zeit versatz der mit der Vorausichtlichen addiert wird was die tatsachliche benoetigte Zeit ergibt 
	unsigned short int Zeitversatz;

	// ein Faktor der zur Berrechnung der vorausichtlichen Zeit benoetigt wird und der einzige auf den der Spieler einen direkten einfluss hat ueber die Upgrades
	float AufgabenDurchfuehrungZeitFaktor;

	//ein Faktor der zur Berrechnung der Ausfuhrungs Kosten benoetigt wird, der Spieler hat auf ihn einen direkten einfluss ueber die Upgrades
	unsigned short int AusfuhrungsKostenFaktor;

	// ein Faktor der zur Berrechnung der vorausichtlichen Zeit benoetigt wird und auf den die einzelnen Gebaude einen individuellen einfluss haben 
	unsigned short int GebaeudeEinflussZeitFaktor;

	//Speichert die Kosten der fuer die Upgrades 
	float UpgradeKosten[3]; // @suppress("Avoid magic numbers")

private:

	//Speichert die Array Position der Aufgaben Kachel des gebaudes 
	short int ProzessHauptKachel;
};

