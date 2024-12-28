#pragma once

#include "../Data/Data.h"
#include "../Menus.h"
#include "../Timer.h"

#include <memory>
#include <sstream>

class Gebaeude : public Timer
{
	public:
	//--------------------------------Konstruktoren----------------------------------------------//
	Gebaeude() = delete;

	// Konstrucktor mit allen informationen fuer eine vollstandige
	// Initzialisierung
	Gebaeude(std::shared_ptr<Data> data, unsigned short int KostenFaktor,
		 unsigned short int ZeitFaktor);
	//--------------------------------Aufgaben
	// Ablauf----------------------------------------------//

	/*
	 Name: GebaeudeAusfuhrungskosten
	 param: keine
	 Aufgabe: Die virtuelle Funktion berechnet wie viel die Ausfuhrung
	 kostet Retrun: Die Funktion gibt die kosten als int zurueck
	 */
	virtual unsigned int getGebaeudeAusfuhrungskosten() const = 0; //NOLINT

	/*
	 Name: BeginnAufgabe
	 param: keine
	 Aufgabe: Die Funktion beginnt die Aufgabe des Gebaudes z.b. beim BAZ
	 der start der Ausbildung Retrun: keine
	 */
	void beginneAufgabe();

	/*
	 Name: aktualisierenProzessZustand
	 param: keine
	 Aufgabe: Die Funktion aktualisiert den Text der Kachel mit dem
	 GebaudeAktivText Retrun: kein
	 */
	inline void aktualisierenProzessZustand();

	/*
	 Name: GebaudeAktivText
	 param: keine
	 Aufgabe: Die virtuelle Funktion erstellt den Text der Angezeigt wird
	 wenn das Gebaude aktiv ist Retrun: Die Funktion gibt den Text als
	 stringstram zurueck
	 */
	virtual const std::stringstream getGebaudeAktivText() const = 0; //NOLINT

	/*
	 Name: BeendenDerAusfuhrung
	 param: keine
	 Aufgabe: Die virtuelle Funktion sorgt fuer ein geregeltes Ende der
	 Ausfuhrung Retrun: keine
	 */
	virtual void beendenDerAusfuhrung() = 0;

	//--------------------------------Upgraden des
	// Gebaeudes----------------------------------------------//

	/*
	 Name: BeschleunigungDerAufgabenDurchfuehrung
	 param: keine
	 Aufgabe: Die Funktion modifiziert den iAufgabenDurchfuehrungZeitFaktor
	 so das die Durchfuerung Schneller ist und passt den Kontostand sowie
	 die Kacheln an Retrun: kein
	 */
	void beschleunigungDerAufgabenDurchfuehrung();

	/*
	 Name: ReduzierenDerAusfuhrungsKosten
	 param: keine
	 Aufgabe: Die Funktion modifiziert den iAusfuhrungsKostenFaktor so das
	 die Durchfuerung der Aufgabe gunstiger ist und passt den Kontostand
	 sowie die Kacheln an Retrun: kein
	 */
	void reduzierenDerAusfuhrungsKosten();

	/*
	 Name: aktualisierenInformationsText
	 param: keine
	 Aufgabe: Die Funktion ermittelt die Zeit die Vorausichtlich fuer die
	 ausfuehrung der Aufgabe gebraucht wird unter Berucksichtigung von den
	 folgenden Faktoren, des iZeitversatz, des iZeitFaktor, des
	 iGeschwindikeitsFaktor und der Bekanntheit Retrun: kein
	 */
	void berrechnungVoraussichtlicheZeit();

	/*
	 Name: aktualisierenTimer
	 param: keine
	 Aufgabe: Die Funktion aktualisiert den Timer und ruft bei Ablauf
	 BeendenDerAusfuhrung auf und wenn der Timer am Ablaufen ist dann wird
	 aktualisierenProzessZustand aufgerufen Retrun: kein
	 */
	void aktualisierenTimer();

	GebaeudeUpgradeStats getUpgradeStats();

	InProgressStats getProgressStats();

	protected:
	// Daten zeiger
	std::shared_ptr<Data> Daten; // NOLINT

	// Wenn true dann wird die Aufgabe Ausgefuhrt der Prozess ist am
	// laufen/aktiv
	bool ProzessAktiv; // NOLINT

	// Gibt an wie lange die Ausbildung vorausichtlich dauert
	unsigned short int VoraussichtlicheZeit; // NOLINT

	// Zeit versatz der mit der Vorausichtlichen addiert wird was die
	// tatsachliche benoetigte Zeit ergibt
	unsigned short int Zeitversatz; // NOLINT

	// ein Faktor der zur Berrechnung der vorausichtlichen Zeit benoetigt
	// wird und der einzige auf den der Spieler einen direkten einfluss hat
	// ueber die Upgrades
	float AufgabenDurchfuehrungZeitFaktor; // NOLINT

	// ein Faktor der zur Berrechnung der Ausfuhrungs Kosten benoetigt wird,
	// der Spieler hat auf ihn einen direkten einfluss ueber die Upgrades
	unsigned short int AusfuhrungsKostenFaktor; // NOLINT

	// ein Faktor der zur Berrechnung der vorausichtlichen Zeit benoetigt
	// wird und auf den die einzelnen Gebaude einen individuellen einfluss
	// haben
	unsigned short int GebaeudeEinflussZeitFaktor; // NOLINT

	// Speichert die Kosten der fuer die Upgrades
	GebaeudeUpgradeStats UpgradeStats; // NOLINT

	InProgressStats ProgressStats; // NOLINT

	private:
	// Speichert die Array Position der Aufgaben Kachel des gebaudes
	short int ProzessHauptKachel;
};
