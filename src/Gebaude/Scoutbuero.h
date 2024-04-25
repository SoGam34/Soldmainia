#pragma once
#include "Gebaeude.h"
#include "Data.h"

class Scoutbuero : public Gebaeude
{
public:
	//--------------------------------Konstruktoren----------------------------------------------//
	Scoutbuero()=delete;

	//Konstrucktor mit allen informationen für eine vollstandige Initzialisierung 
	Scoutbuero(std::shared_ptr<Data> data, std::mutex& mutex);
	~Scoutbuero();		

	//--------------------------------Aufgaben Ablauf----------------------------------------------//
	
	/*
	Name: GebaeudeAusfuhrungskosten
	param: keine 
	Aufgabe: Die Funktion berechnet wie viel die Ausfuhrung kostet
	Retrun: Die Funktion gibt die kosten als int zurück
	Zu Beachten: Die Funktion ist in gebaude als virtuell deklarirt 
	*/
	unsigned const int GebaeudeAusfuhrungskosten() const;

	/*
	Name: GebaudeAktivText
	param: keine 
	Aufgabe: Die Funktion erstellt den Text der Angezeigt wird wenn das Gebaude aktiv ist 
	Retrun: Die Funktion gibt den Text als stringstram zurück
	Zu Beachten: Die Funktion ist in gebaude als virtuell deklarirt 
	*/
	const std::stringstream GebaudeAktivText() const;
	
	/*
	Name: BeendenDerAusfuhrung
	param: keine 
	Aufgabe: Die Funktion sorgt für ein geregeltes Ende der Ausfuhrung  
	Retrun: keine
	Zu Beachten: Die Funktion ist in gebaude als virtuell deklarirt 
	*/
	void BeendenDerAusfuhrung();
	
	/*
	Name: Annehmen
	param: keine 
	Aufgabe: Die  Funktion fuegt das EM hinzu und stellt die Aufgaben anzige auf Informationtext um Anzeige
	Retrun: keine
	*/
	void Annehmen();
	
	/*
	Name: Ablehnen
	param: keine 
	Aufgabe: Die Funktion loescht das EM und stellt die Aufgaben anzige auf Informationtext um Anzeige
	Retrun: keine
	*/
	void Ablehnen();
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
	Name: ErhohenDesMoeglichenRanges
	param: keine 
	Aufgabe: Die Funktion modifiziert iRangmin, so das die Em`s die gefunden werden einen hoheren Rang haben und passt den Kontostand sowie die Kacheln an
	Retrun: keine
	*/
	void ErhohenDesMoeglichenRanges();

private:
	// Der mindest Rang den ein EM haben kann
	int iRangmin;
	// Fuer eine einfachere Verwaltung der Suche und Erzeugung
	enum Rang { S = 7, A = 6, B = 5, C = 4, D = 3, E = 2, F = 1 };
	//Das Objekt in dem der aktuelle Rang gespeichrt wird 
	Rang eRang;
};

