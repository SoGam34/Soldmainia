#pragma once
#include "Gebaeude.h"
#include "Auswahl.h"

class Erholungsresort : public Gebaeude, public Auswahl
{
public:
	//--------------------------------Konstruktoren----------------------------------------------//
	Erholungsresort() = delete;

	//Konstrucktor mit allen informationen f�r eine vollstandige Initzialisierung
	Erholungsresort(std::shared_ptr<Data> data, std::mutex& mutex);
	~Erholungsresort();

	//--------------------------------Aufgaben Ablauf----------------------------------------------//

	/*
	Name: GebaeudeAusfuhrungskosten
	param: keine
	Aufgabe: Die Funktion berechnet wie viel die Ausfuhrung kostet
	Retrun: Die Funktion gibt die kosten als int zur�ck
	Zu Beachten: Die Funktion ist in gebaude als virtuell deklarirt
	*/
	unsigned const int GebaeudeAusfuhrungskosten() const;

	/*
	Name: AuswahlZuOrdnen
	param: std::string Name -> Der Name der Einheit die vom Spieler ausgewahlt wurde
	Aufgabe: Die Funktion speichert den Namen der Ausgewahlten Einheit und startet die Ausbildung
	Retrun: keine
	*/
	void AuswahlZuOrdnen(int Position, std::mutex& mutex);

	/*
	Name: GebaudeAktivText
	param: keine
	Aufgabe: Die Funktion erstellt den Text der Angezeigt wird wenn das Gebaude aktiv ist
	Retrun: Die Funktion gibt den Text als stringstram zur�ck
	Zu Beachten: Die Funktion ist in gebaude als virtuell deklarirt
	*/
	const std::stringstream GebaudeAktivText() const;

	/*
	Name: BeendenDerAusfuhrung
	param: keine
	Aufgabe: Die Funktion sorgt f�r ein geregeltes Ende der Ausfuhrung
	Retrun: keine
	Zu Beachten: Die Funktion ist in gebaude als virtuell deklarirt
	*/
	void BeendenDerAusfuhrung();

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
	void ErhohenDerTraningsWirksamkeit();

private:
	//Speichert den Namen der Einheit die Traniert wird 
	int EinheitsVPosition;

	//Speichert den Wirksamkeitsgrad und ist damit ein wichtiger Faktor in der Berrechnung der Xp die die Einheit bekommt und kann vom Spieler veraendert werden
	unsigned short int iWirksamkeitsgrad;
};

