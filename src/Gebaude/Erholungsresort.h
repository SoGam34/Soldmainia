#pragma once
#include "Gebaeude.h"
#include "../Auswahl.h"
#include "../Data/Data.h"
#include "../Timer.h"

#include <memory>
#include <sstream>
class Erholungsresort: public Gebaeude, public Auswahl
{
public:
	//--------------------------------Konstruktoren----------------------------------------------//
	Erholungsresort() = delete;

	//Konstrucktor mit allen informationen fuer eine vollstandige Initzialisierung
	Erholungsresort(std::shared_ptr<Data> data);
	~Erholungsresort();

	//--------------------------------Aufgaben Ablauf----------------------------------------------//

	/*
	 Name: GebaeudeAusfuhrungskosten
	 param: keine
	 Aufgabe: Die Funktion berechnet wie viel die Ausfuhrung kostet
	 Retrun: Die Funktion gibt die kosten als int zurueck
	 Zu Beachten: Die Funktion ist in gebaude als virtuell deklarirt
	 */
	unsigned int getGebaeudeAusfuhrungskosten() const;

	/*
	 Name: AuswahlZuOrdnen
	 param: std::string Name -> Der Name der Einheit die vom Spieler ausgewahlt wurde
	 Aufgabe: Die Funktion speichert den Namen der Ausgewahlten Einheit und startet die Ausbildung
	 Retrun: keine
	 */
	void auswahlZuOrdnen(int Position);

	/*
	 Name: GebaudeAktivText
	 param: keine
	 Aufgabe: Die Funktion erstellt den Text der Angezeigt wird wenn das Gebaude aktiv ist
	 Retrun: Die Funktion gibt den Text als stringstram zurueck
	 Zu Beachten: Die Funktion ist in gebaude als virtuell deklarirt
	 */
	const std::stringstream getGebaudeAktivText() const;

	/*
	 Name: BeendenDerAusfuhrung
	 param: keine
	 Aufgabe: Die Funktion sorgt fuer ein geregeltes Ende der Ausfuhrung
	 Retrun: keine
	 Zu Beachten: Die Funktion ist in gebaude als virtuell deklarirt
	 */
	void beendenDerAusfuhrung();

	//--------------------------------Allgemeine Funktionen Gebaeudes----------------------------------------------//

	/*
	 Name: aktualisierenInformationsText
	 param: keine
	 Aufgabe: Die Funktion aktualisiert den Informationstext sodass der Spieler weis was die Aufgabe des gebaudes ist und unter welchen Bedingungen diese Erfullt wird
	 Retrun: kein
	 Zu Beachten: Die Funktion ist in gebaude als virtuell deklarirt
	 */
	inline void aktualisierenInformationsText();

	//--------------------------------Upgraden des Gebaeudes----------------------------------------------//

	/*
	 Name: ErhohenDerTraningsWirksamkeit
	 param: keine
	 Aufgabe: Die Funktion modifiziert den Wirksamkeitsgrad, so das die Einheiten mehr XP erhalten und passt den Kontostand sowie die Kacheln an
	 Retrun: keine
	 */
	void erhohenDerTraningsWirksamkeit();

private:
	//Speichert den Namen der Einheit die Traniert wird 
	int EinheitsVPosition;

	//Speichert den Wirksamkeitsgrad und ist damit ein wichtiger Faktor in der Berrechnung der Xp die die Einheit bekommt und kann vom Spieler veraendert werden
	unsigned short int Wirksamkeitsgrad;
};

