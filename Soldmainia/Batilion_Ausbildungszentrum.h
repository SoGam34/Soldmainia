#pragma once
#include "Gebaeude.h"
#include "Data.h"

class Batilion_Ausbildungszentrum : public Gebaeude
{
public:
	//--------------------------------Konstruktoren----------------------------------------------//
	Batilion_Ausbildungszentrum()=delete;

	//Konstrucktor mit allen informationen für eine vollstandige Initzialisierung 
	Batilion_Ausbildungszentrum(Data* data);
	~Batilion_Ausbildungszentrum();

	//--------------------------------Aufgaben Ablauf----------------------------------------------//
	
	/*
	Name: GebaeudeAusfuhrungskosten
	param: keine 
	Aufgabe: Die virtuelle Funktion berechnet wie viel die Ausfuhrung kostet
	Retrun: Die Funktion gibt die kosten als int zurück
	Zu Beachten: Die Funktion ist in gebaude als virtuell deklarirt 
	*/
	unsigned const int GebaeudeAusfuhrungskosten() const;

	/*
	Name: GebaudeAktivText
	param: keine 
	Aufgabe: Die virtuelle Funktion erstellt den Text der Angezeigt wird wenn das Gebaude aktiv ist 
	Retrun: Die Funktion gibt den Text als stringstram zurück
	Zu Beachten: Die Funktion ist in gebaude als virtuell deklarirt 
	*/
	const std::stringstream GebaudeAktivText() const;
	
	/*
	Name: AnzahlErhohen
	param: keine 
	Aufgabe: Die Funktion erhot die Groeße des Batilions was ausgebildet werden soll
	Retrun: keine
	*/
	void AnzahlErhohen();

	/*
	Name: AnzahlReduzieren
	param: keine 
	Aufgabe: Die Funktion rediziert die Groeße des Batilions was ausgebildet werden soll
	Retrun: keine
	*/
	void AnzahlReduzieren();

	/*
	Name: BeendenDerAusfuhrung
	param: keine 
	Aufgabe: Die virtuelle Funktion sorgt für ein geregeltes Ende der Ausfuhrung  
	Retrun: keine
	Zu Beachten: Die Funktion ist in gebaude als virtuell deklarirt 
	*/
	void BeendenDerAusfuhrung();

	/*
	Name: Vorbereiten_neueAusbildung
	param: keine 
	Aufgabe: Die Funktion bereitet alles für eine neue Ausbildung vor 
	Retrun: keine
	*/
	void Vorbereiten_neueAusbildung();

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
	Name: ErhohenDerGrundstarke
	param: keine 
	Aufgabe: Die Funktion modifiziert fGrundstaerke, sodass das Batilion starker ist und passt den Kontostand sowie die Kacheln an
	Retrun: keine
	*/
	void ErhohenDerGrundstarke();

private:
	unsigned short int iBatilionsgroeße = 10;
	float fGrundstaerke = 10;
};

