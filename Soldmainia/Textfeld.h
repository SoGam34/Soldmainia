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
	//Konstrucktor mit allen informationen f�r eine vollstandige Initzialisierung
	Textfeld(const sf::Color farbe, const sf::Font &font, const sf::Vector2f pos);

	~Textfeld();

	//--------------------------------Input----------------------------------------------//

	/*
	Name: ueberpruefeObEnterGedrueckt
	param:  sf::Event& event -> Speichert die Information welche Taste gedr�ckt wurde
	Aufgabe: Anhangen eines neuen Button an den vButton Vektor
	Retrun: keine
	*/
	bool ueberpruefeObEnterGedrueckt(const sf::Event& event);

	/*
	Name: ButtonHinzufuegen
	param: sf::Event& event -> Speichert die Information welche Taste gedr�ckt wurde
	Aufgabe: Kontroliert ob ein sinnvoller Bustabe gedruckt wurde wenn ja wird er angehangt
	Retrun: keine
	*/
	void BuchstabeGedr�ckt(const sf::Event& event);

	/*
	Name: setTextfeldAusgewahlt
	param: bool auswahl -> Der neue status des textfeldes 
	Aufgabe: �ndert den Status des Textfeldes und entfernt oder f�gt ein _ hinzu um zu zeigen welchen Status das Textfeld hat
	Retrun: keine
	*/
	void setTextfeldAusgewahlt(bool auswahl);

	//--------------------------------Get/Set----------------------------------------------//

	/*
	Name: getAusgewahlt
	param: keine
	Aufgabe: Die Funktion gibt den Status des Textfelds zur�ck
	Retrun: Die Funktion gibt den Status als bool zur�ck
	*/
	const inline bool getAusgewahlt() const;
	
	/*
	Name: getPosition
	param: keine
	Aufgabe: Die Funktion gibt die aktuelle Position des textfeldes zur�ck
	Retrun: Die Funktion gibt die Koordinaten als sf::Vector2f zur�ck
	*/
	const inline sf::Vector2f getPosition() const;

	/*
	Name: getBegrenzungen
	param: keine
	Aufgabe: Die Funktion gibt die Begrenzungen des Textfelds zur�ck
	Retrun: Die Funktion gibt die Begrenzung als sf::FloatRect zur�ck
	*/
	const inline sf::FloatRect getBegrenzungen() const;

	/*
	Name: getText
	param: keine
	Aufgabe: Die Funktion gibt den Text zur�ck
	Retrun: Die Funktion gibt Text als string zur�ck
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

	//Die Methode f�gt den Text hinzu und behandelt ausnahme Falle 
	void inputlogic(int Buch);
};

