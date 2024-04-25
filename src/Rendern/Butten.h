#pragma once

class Button
{
public:
	//--------------------------------Konstruktoren----------------------------------------------//
	Button()=delete;

	//Konstrucktor mit allen informationen fuer eine vollstandige Initzialisierung 
	Button(float Button_x, float Button_y, float Button_Breite, float Button_Hohe, unsigned int Button_ID,
		std::string Button_Text, sf::Font& font,
		sf::Color Button_Hintergrundfarbe, sf::Color Button_Schwebefarbe, sf::Color Button_Gedruecktfarbe, sf::Color Button_Textfarbe,
		float Kachel_Breite, float Kachel_Hohe);
	~Button();

	//--------------------------------Zustand und Position----------------------------------------------//

	/*
	Name: wirdGedrueckt
	param: keine 
	Aufgabe: Die Funktion ueberpruft ob der Button gedrueckt wird 
	Retrun: Die Funktion gibt true zurueck wenn die Maus gedrueckt wird und der Button in nicht gedrueckten Zustand ist ansonsten wird false zurueckgegeben
	*/
	bool wirdGedrueckt();

	/*
	Name: MausSchwebtdrueber
	param: sf::Vector2i& mouspos -> Die aktuelle Maus Position  
	Aufgabe: Die Funktion ueberpruft ob die Maus sich ueber dem Button befindet
	Retrun: Die Funktion gibt true zurueck wenn die Maus sich ueber dem Button befindet ansonsten wird false zurueckgegeben
	*/
	bool MausSchwebtDrueber(const sf::Vector2i& mouspos);

	/*
	Name: aktualisieren
	param: keine 
	Aufgabe: Die Funktion aktualisiert den Gedrueckt Zustand indem sie den Timer, der Zahlt wie lange der Butten sich im gedrueckt Zustand befindet, runterzahlt  
	Retrun: keinen
	*/
	void aktualisieren();
	
	/*
	Name: aktualisierenPosition
	param: float Button_x -> , float Button_y, float Button_Breite, float Button_Hohe 
	Aufgabe: Die Funktion ueberschreibt die Position und die Masse des Buttons
	Retrun: keinen
	*/
	void aktualisierenPosition(float Button_x, float Button_y, float Button_Breite, float Button_Hohe);

	//--------------------------------Farben----------------------------------------------//

	/*
	Name: setButton_Gedruecktfarbe
	param: keine 
	Aufgabe: Die Funktion setzt die Farbe des Button auf die bei der Initzalisierung uebergebene gedruecktfarbe
	Retrun: keine
	*/
	const void setButton_Gedruecktfarbe();

	/*
	Name: setButton_Schwebefarbe
	param: keine 
	Aufgabe: Die Funktion setzt die Farbe des Button auf die bei der Initzalisierung uebergebene Schwebefarbe
	Retrun: keine
	*/
	const void setButton_Schwebefarbe();
	
	/*
	Name: setButton_Hintergrundfarbe
	param: keine 
	Aufgabe: Die Funktion setzt die Farbe des Button auf die bei der Initzalisierung uebergebene Hintergrundfarbe
	Retrun: keine
	*/
	const void setButton_Hintergrundfarbe();

	//--------------------------------Get----------------------------------------------//

	/*
	Name: getID
	param: keine 
	Aufgabe: Die Funktion gibt die bei der Initizalisierung uebergeben ID zurueck 
	Retrun: Die ID des Button als int 
	*/
	const  unsigned int getID() const;

	/*
	Name: getPosition
	param: keine 
	Aufgabe: Die Funktion gibt die Position des Button zurueck
	Retrun: Die Funktion gibt die Positon als sf::Vector2f zurueck 
	*/
	const  sf::Vector2f getPosition() const;

	/*
	Name: getGroese
	param: keine 
	Aufgabe: Die Funktion gibt die Hohe und Breite des Button zurueck 
	Retrun: Die Funktion gibt die Hohe und Breite als sf::Vector2f zurueck
	*/
	const  sf::Vector2f getGroese() const;

	//--------------------------------Anzeigen----------------------------------------------//

	/*
	Name: drawFenster
	param: Das Window auf dem das Spiel lauft  
	Aufgabe: Die Funktion mahlt den Button Shape auf das Fenster
	Retrun: keinen
	*/
	 void drawFenster(sf::RenderTarget& target);

	/*
	Name: drawText
	param: Das Window auf dem das Spiel lauft  
	Aufgabe: Die Funktion mahlt den Text des Button auf das Fenster
	Retrun: keinen
	*/
	 void drawText(sf::RenderTarget& target);

private:

	// Die Variable speichert die Groeße, die aktuelle Farbe, die Position und wird auf das Spiel window gemalt
	sf::RectangleShape sf_rsButton;

	//Die Variable speichert den Text des Buttons, die Position des Textes, den Font und die Textfarbe und wird auf das Spiel window gemalt
	sf::Text sf_tText;

	//Die Variablen speichern die Farbwerte welche der Button in den entsprechenden Fallen annimmt. Wird in den Farben set funktionen verwendet.
	sf::Color sf_cHintergrundfarbe, sf_cSchwebefarbe, sf_cGedruecktfarbe;

	//Speichert die ID des Buttens welche die Game Klasse fuer die Zuordnung der Funktion des Buttons benoetigt und fuer Kachel zur ueberpruefung welcher Button gedrueckt wird 
	const unsigned iID;

	//Die Variable speichert ob der Button gedrueckt wurde um unbeabsichtigtes druecken zu verhindern 
	bool bDruecken;

	//Die Variable speichert wie lange die gedrueckt Farbe angezeigt werden soll. Die Variable fungiert wie eine art Timer, damit der User sieht, dass das System das druecken Registriert hat. 
	int iVerbleibendeDrueckZeit;

	//Die Variable speichert das Verhaltniss zur zugehorige Kachel damit das Verhaltniss von Button, Kachel und Fenster bestehen bleibt 
	float fFactorBreite;

	//Die Variable speichert das Verhaltniss zur zugehorige Kachel damit das Verhaltniss von Button, Kachel und Fenster bestehen bleibt 
	float fFactorHohe;
};

