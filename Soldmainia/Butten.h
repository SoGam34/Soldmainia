#pragma once

class Button
{
public:
	//--------------------------------Konstruktoren----------------------------------------------//
	Button()=delete;

	//Konstrucktor mit allen informationen für eine vollstandige Initzialisierung 
	Button(float Button_x, float Button_y, float Button_Breite, float Button_Hohe, int Button_ID,
		std::string Button_Text, sf::Font& font,
		sf::Color Button_Hintergrundfarbe, sf::Color Button_Schwebefarbe, sf::Color Button_Gedrücktfarbe, sf::Color Button_Textfarbe,
		float Kachel_Breite, float Kachel_Hohe);
	~Button();

	//--------------------------------Zustand und Position----------------------------------------------//

	/*
	Name: wirdGedrückt
	param: keine 
	Aufgabe: Die Funktion überpruft ob der Button gedrückt wird 
	Retrun: Die Funktion gibt true zurück wenn die Maus gedrückt wird und der Button in nicht gedrückten Zustand ist ansonsten wird false zurückgegeben
	*/
	bool wirdGedrückt();

	/*
	Name: MausSchwebtdrüber
	param: sf::Vector2i& mouspos -> Die aktuelle Maus Position  
	Aufgabe: Die Funktion überpruft ob die Maus sich über dem Button befindet
	Retrun: Die Funktion gibt true zurück wenn die Maus sich über dem Button befindet ansonsten wird false zurückgegeben
	*/
	bool MausSchwebtDrüber(sf::Vector2i& mouspos);

	/*
	Name: aktualisieren
	param: keine 
	Aufgabe: Die Funktion aktualisiert den Gedrückt Zustand indem sie den Timer, der Zahlt wie lange der Butten sich im gedrückt Zustand befindet, runterzahlt  
	Retrun: keinen
	*/
	void aktualisieren();
	
	/*
	Name: aktualisierenPosition
	param: float Button_x -> , float Button_y, float Button_Breite, float Button_Hohe 
	Aufgabe: Die Funktion überschreibt die Position und die Masse des Buttons
	Retrun: keinen
	*/
	void aktualisierenPosition(float Button_x, float Button_y, float Button_Breite, float Button_Hohe);

	//--------------------------------Farben----------------------------------------------//

	/*
	Name: setButton_Gedrücktfarbe
	param: keine 
	Aufgabe: Die Funktion setzt die Farbe des Button auf die bei der Initzalisierung übergebene gedrücktfarbe
	Retrun: keine
	*/
	void setButton_Gedrücktfarbe();

	/*
	Name: setButton_Schwebefarbe
	param: keine 
	Aufgabe: Die Funktion setzt die Farbe des Button auf die bei der Initzalisierung übergebene Schwebefarbe
	Retrun: keine
	*/
	void setButton_Schwebefarbe();
	
	/*
	Name: setButton_Hintergrundfarbe
	param: keine 
	Aufgabe: Die Funktion setzt die Farbe des Button auf die bei der Initzalisierung übergebene Hintergrundfarbe
	Retrun: keine
	*/
	void setButton_Hintergrundfarbe();

	//--------------------------------Get----------------------------------------------//

	/*
	Name: getID
	param: keine 
	Aufgabe: Die Funktion gibt die bei der Initizalisierung übergeben ID zurück 
	Retrun: Die ID des Button als int 
	*/
	int getID();

	/*
	Name: getPosition
	param: keine 
	Aufgabe: Die Funktion gibt die Position des Button zurück
	Retrun: Die Funktion gibt die Positon als sf::Vector2f zurück 
	*/
	sf::Vector2f getPosition();

	/*
	Name: getGroese
	param: keine 
	Aufgabe: Die Funktion gibt die Hohe und Breite des Button zurück 
	Retrun: Die Funktion gibt die Hohe und Breite als sf::Vector2f zurück
	*/
	sf::Vector2f getGroese();

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

	// Die Variable speichert die Größe, die aktuelle Farbe, die Position und wird auf das Spiel window gemalt
	sf::RectangleShape sf_rsButton;

	//Die Variable speichert den Text des Buttons, die Position des Textes, den Font und die Textfarbe 
	sf::Text sf_tText;

	//Die Variablen speichern die Farbwerte welche der Button in den entsprechenden Fallen annimmt. Wird in den Farben set funktionen verwendet.
	sf::Color sf_cHintergrundfarbe, sf_cSchwebefarbe, sf_cGedrücktfarbe;

	//Speichert die ID des Buttens welche die Game Klasse für die Zuordnung der Funktion des Buttons benötigt und für Kachel zur Überprüfung welcher Button gedrückt wird 
	int iID;

	//Die Variable speichert ob der Button gedrückt wurde um unbeabsichtigtes drücken zu verhindern 
	bool bDruecken;

	//Die Variable speichert wie lange die gedrückt Farbe angezeigt werden soll. Die Variable fungiert wie eine art Timer, damit der User sieht, dass das System das drücken Registriert hat. 
	int iVerbleibendeDrueckZeit;

	//Die Variable speichert das Verhaltniss zur zugehorige Kachel damit das Verhaltniss von Button, Kachel und Fenster bestehen bleibt 
	float fFactorBreite;

	//Die Variable speichert das Verhaltniss zur zugehorige Kachel damit das Verhaltniss von Button, Kachel und Fenster bestehen bleibt 
	float fFactorHohe;
};

