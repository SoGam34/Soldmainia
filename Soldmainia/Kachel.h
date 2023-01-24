#pragma once

class Kachel
{
public:

	//--------------------------------Konstruktoren----------------------------------------------//

	Kachel()=delete;  

	//Konstrucktor mit allen informationen für eine vollstandige Initzialisierung  
	Kachel(std::string Text, int PosTextY, sf::Color TextColor, sf::Font* font,
		int IDTexture, int PosTextureX, int PosTextureY,
		int ID, int PosKachelX, int PosKachelY, float with, float height,
		sf::Color backroundColor, sf::Color hoverColor, sf::Color pressColor);
	~Kachel();

	//--------------------------------Button Verwaltung----------------------------------------------//

	/*
	Name: ButtonHinzufuegen
	param: alle die ein Button zur Initialisierung benötigt 
	Aufgabe: Anhangen eines neuen Button an den vButton Vektor 
	Retrun: keine
	*/
	void ButtonHinzufuegen(float x, float y, float with, float heigth, int ID,
						std::string text, sf::Font* font,
						sf::Color backroundColor, sf::Color hoverColor, sf::Color PressColor, sf::Color textColor,
						float KachelBreite, float KachelHohe);
	
	/*
	Name: ueberprueftAlleButtonObMausSchwebtDrüber
	param: sf::Vector2i mouspos -> Die aktuelle Maus Position
	Aufgabe: Die Funktion geht alle Button durch und uberpruft ob der Mauszeiger sich über einem Button befindet 
	Retrun: wenn der Mauszeiger sich über einem Button befindet wird die ID des Butten zurück gegeben an sonsten wird nichts zurück gegeben
	*/
	std::optional<int> ueberprueftAlleButtonObMausSchwebtDrüber(sf::Vector2i& mouspos);

	/*
	Name: ueberprueftAlleButtonObGedruektWird
	param: int ButtenID -> Die ID des Button überdem der Mauszeiger sich befindet  
	Aufgabe: überprüft ob der Button gedrückt wird 
	Return: wenn der Button gedrückt wird gibt die Funktion true zurück ansonsten wird false zurück gegeben 
	*/
	bool ueberprueftButtonObGedruektWird(int ButtenID);

	/*
	Name: setAlleButtenAufHintergrundfarbe
	param: keine
	Aufgabe: Geht alle Button in vButton durch und setzt alle auf die Hintergrundfarbe  
	Retrun: keine
	*/
	void setAlleButtenAufHintergrundfarbe();

	

	//--------------------------------Textfeld Verwaltung----------------------------------------------//
	
	/*
	Name: TextfeldHinzufuegen
	param: alle param die Textfeld zur Initialisierung benötigt 
	Aufgabe: Initialisiert oder überschreibt cTextfeld mit einem Neuem Textfeldobjekt das mit den param erstellt wurde
	Retrun: keine
	*/
	void TextfeldHinzufuegen(sf::Color farbe, sf::Font *font, sf::Vector2f pos);
	
	
	/*
	Name: aktualisierenTextfelder
	param: sf::Event& event -> Speichert die Information welche Taste gedrückt wurde, sf::Vector2i MousPos -> Die aktuelle Mauszeiger Position 
	Aufgabe: Wenn es ein Textfeld gibt wird die Tasten information an Textfeld weitergereicht
	Retrun: keine
	*/
	void aktualisierenTextfelder(sf::Event& event, sf::Vector2i& MousPos);

	/*
	Name: ueberpruefenObEnterGedruekt
	param: sf::Event& event -> Speichert die Information welche Taste gedrückt wurde
	Aufgabe: Wenn es ein Textfeld gibt wird die Tasten information an Textfeld weitergereicht. Die Klasse überpruft ob enter gedruckt wurde das Ergebniss wird an ueberpruefenObEnterGedruekt zurück gegeben.
	Retrun: Wenn Textfeld vorhanden dann wird das Ergbniss weitergereicht ansonsten wird false zurück gegeben
	*/
	bool ueberpruefenObEnterGedruekt(sf::Event& event);
	
	/*
	Name: getTextfeldAusgewahltStatus
	param: keine
	Aufgabe: Den Status von dem Textfeld zurück geben 
	Retrun:  Wenn ein Textfeld vorhanden ist wird der Ausgewahlt Status zurück gegeben ansonsten wird false zurück gegeben 
	*/
	bool getTextfeldAusgewahltStatus();

	//--------------------------------Kachel Verwaltung----------------------------------------------//

	/*
	Name: neueAnzeige
	param: std::string Text -> Der Text der Angezeigt werden soll, int PosTextY -> Die Position der Oberkante des Textes, 
				int IDTexture -> Die Nummer des Textuers was Angezeigt werden soll, int PosTextureX -> Die X- Position des Texture , int PosTextureY -> Die Y-Position des Textures
	Aufgabe: Das Löschen aller Buttons und Textfelder und das überschreiben der modifizierbaren Eigenschaften der Kachel
	Retrun: keine
	*/
	void neueAnzeige(std::string Text, int PosTextY, 
				int IDTexture, int PosTextureX, int PosTextureY);

	/*
	Name: TextAendern
	param: std::string Text -> Der Text der Angezeigt werden soll, int PosTextY -> Die Position der Oberkante des Textes
	Aufgabe: Die Funktion überschreibt den Text der Kachel und die y - Koordinate des Textes 
	Retrun: keine
	*/
	void TextAendern(std::string Text, int PosTextY);

	/*
	Name: aktualisierenPosition
	param: float Kachel_x -> Die neue X Koordienate der Kachel, float Kachle_y -> Die neue Y Koordienate der Kachel, float Kachel_Breite -> Die neue Breite der Kachel, float Kachel_Hohe -> Die neue Hohe der Kachel
	Aufgabe: Die Funktion überschreibt die Position und die Masse des Buttons
	Retrun: keinen
	*/
	void aktualisierenPosition(float Button_x, float Button_y, float Button_Breite, float Button_Hohe);
	
	/*
	Name: aktualisieren
	param: keine
	Aufgabe: Die Funktion aktualisiert den Gedrückt Zustand indem sie den Timer, der Zahlt wie lange der Butten sich im gedrückt Zustand befindet, runterzahlt und ruft Button aktualisieren auf
	Retrun: keinen
	*/
	void aktualisieren();

	/*
	Name: wirdGedrückt
	param: keine
	Aufgabe: Die Funktion überpruft ob die Kachel gedrückt wird
	Retrun: Die Funktion gibt true zurück wenn die Maus gedrückt wird und die Kachel in nicht gedrückten Zustand ist ansonsten wird false zurückgegeben
	*/
	bool wirdGedrückt();

	/*
	Name: MausSchwebtdrüber
	param: sf::Vector2i& mouspos -> Die aktuelle Maus Position
	Aufgabe: Die Funktion überpruft ob die Maus sich über der Kachel befindet
	Retrun: Die Funktion gibt true zurück wenn die Maus sich über der Kachel befindet ansonsten wird false zurückgegeben
	*/
	bool MausSchwebtDrüber(sf::Vector2i& mouspos);
	
	/*
	Name: drawFenster
	param: Das Window auf dem das Spiel lauft
	Aufgabe: Die Funktion mahlt den Kachel und die Button Shapes auf das Fenster
	Retrun: keinen
	*/
	void drawFenster(sf::RenderTarget& target);
	
	/*
	Name: drawText
	param: Das Window auf dem das Spiel lauft
	Aufgabe: Die Funktion mahlt den Kachel und die Button Texte auf das Fenster
	Retrun: keinen
	*/
	void drawText(sf::RenderTarget& target);

	//--------------------------------Kachel Farben----------------------------------------------//

	/*
	Name: setKachel_Gedrücktfarbe
	param: keine
	Aufgabe: Die Funktion setzt die Farbe der Kachel auf die bei der Initzalisierung übergebene gedrücktfarbe
	Retrun: keine
	*/
	void setKachel_Gedrücktfarbe();

	/*
	Name: setKachel_Schwebefarbe
	param: keine
	Aufgabe: Die Funktion setzt die Farbe der Kachel auf die bei der Initzalisierung übergebene Schwebefarbe
	Retrun: keine
	*/
	void setKachel_Schwebefarbe();

	/*
	Name: setKachel_Hintergrundfarbe
	param: keine
	Aufgabe: Die Funktion setzt die Farbe der Kachel auf die bei der Initzalisierung übergebene Hintergrundfarbe
	Retrun: keine
	*/
	void setKachel_Hintergrundfarbe();

	//--------------------------------Get/Set----------------------------------------------//

	void setSize(sf::Vector2f posKachel, sf::Vector2f posTex, sf::Vector2f size);

	void setScale(float sice);

	int getID();
	
	int getTextureID();

	float getScale();
	
	sf::Vector2f getTexturePosition();

	void setTexturePosition(sf::Vector2f pos);
	
	sf::Vector2f getPos();
	
	sf::Vector2f getSize();

	private:
	//Kachel
	sf::RectangleShape kachel;
	sf::Text tText;
	sf::Color sfBackroundColor, sfHoverColor, sfPressColor;
	bool bdruken;
	int iID;
	int PressTimer;
	void newText(std::string Text, int PosTextY);
	int NormalPos;
	//Texture
	int iIDTexture;
	sf::Vector2f TexturePos;

	//Butten
	std::unordered_map<int, Button*> vButton;
	float TextureScale;

	//Textfeld
	Textfeld* cTextfeld;
};

