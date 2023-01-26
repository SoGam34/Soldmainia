#pragma once

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class Textfeld
{
public:

	//--------------------------------Konstruktoren----------------------------------------------//

	//Textfeld()= delete;
	Textfeld();
	//Konstrucktor mit allen informationen für eine vollstandige Initzialisierung
	Textfeld(const sf::Color farbe, const sf::Font &font, const sf::Vector2f pos);

	~Textfeld();

	//--------------------------------Input----------------------------------------------//

	/*
	Name: ueberpruefeObEnterGedrueckt
	param:  sf::Event& event -> Speichert die Information welche Taste gedrückt wurde
	Aufgabe: Anhangen eines neuen Button an den vButton Vektor
	Retrun: keine
	*/
	bool ueberpruefeObEnterGedrueckt(const sf::Event& event);

	/*
	Name: ButtonHinzufuegen
	param: sf::Event& event -> Speichert die Information welche Taste gedrückt wurde
	Aufgabe: Kontroliert ob ein sinnvoller Bustabe gedruckt wurde wenn ja wird er angehangt
	Retrun: keine
	*/
	void BuchstabeGedrückt(const sf::Event& event);

	/*
	Name: setTextfeldAusgewahlt
	param: bool auswahl -> Der neue status des textfeldes 
	Aufgabe: Ändert den Status des Textfeldes und entfernt oder fügt ein _ hinzu um zu zeigen welchen Status das Textfeld hat
	Retrun: keine
	*/
	void setTextfeldAusgewahlt(bool auswahl);

	//--------------------------------Get/Set----------------------------------------------//

	/*
	Name: getAusgewahlt
	param: keine
	Aufgabe: Die Funktion gibt den Status des Textfelds zurück
	Retrun: Die Funktion gibt den Status als bool zurück
	*/
	const inline bool getAusgewahlt() const;
	
	/*
	Name: getPosition
	param: keine
	Aufgabe: Die Funktion gibt die aktuelle Position des textfeldes zurück
	Retrun: Die Funktion gibt die Koordinaten als sf::Vector2f zurück
	*/
	const inline sf::Vector2f getPosition() const;

	/*
	Name: getBegrenzungen
	param: keine
	Aufgabe: Die Funktion gibt die Begrenzungen des Textfelds zurück
	Retrun: Die Funktion gibt die Begrenzung als sf::FloatRect zurück
	*/
	const inline sf::FloatRect getBegrenzungen() const;

	/*
	Name: getText
	param: keine
	Aufgabe: Die Funktion gibt den Text zurück
	Retrun: Die Funktion gibt Text als string zurück
	*/
	const inline std::string getText() const;

	//--------------------------------Anzeigen----------------------------------------------//
	
	/*
	Name: drawText
	param: Das Window auf dem das Spiel lauft
	Aufgabe: Die Funktion mahlt den Text des Textfeldes auf das Fenster
	Retrun: keinen
	*/
	void drawText(sf::RenderTarget& target);

private:
	//Die Variable speichert den Text des Textfeld, die Position des Textes, den Font und die Textfarbe und wird auf das Spiel window gemalt
	sf::Text sf_tTextfeld;

	//
	std::ostringstream oText;

	//Speichert den status des Testfeldes 
	bool bAusgewalt;

	//Die Methode fügt den Text hinzu und behandelt ausnahme Falle 
	void inputlogic(int Buch);
};

