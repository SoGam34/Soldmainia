#pragma once

class Kachel
{
public:

	//--------------------------------Konstruktoren----------------------------------------------//

	Kachel()=delete;  

	//Konstrucktor mit allen informationen für eine vollstandige Initzialisierung  
	Kachel(std::string Text, int PosTextY, sf::Color TextColor, sf::Font& font,
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
	inline void ButtonHinzufuegen(float x, float y, float with, float heigth, int ID,
						std::string text, sf::Font& font,
						sf::Color backroundColor, sf::Color hoverColor, sf::Color PressColor, sf::Color textColor,
						float KachelBreite, float KachelHohe);
	
	/*
	Name: ueberprueftAlleButtonObMausSchwebtDrüber
	param: sf::Vector2i mouspos -> Die aktuelle Maus Position
	Aufgabe: Die Funktion geht alle Button durch und uberpruft ob der Mauszeiger sich über einem Button befindet 
	Retrun: wenn der Mauszeiger sich über einem Button befindet wird die ID des Butten zurück gegeben an sonsten wird nichts zurück gegeben
	*/
	std::optional<unsigned int> ueberprueftAlleButtonObMausSchwebtDrüber(const sf::Vector2i& mouspos);

	/*
	Name: ueberprueftAlleButtonObGedruektWird
	param: int ButtenID -> Die ID des Button überdem der Mauszeiger sich befindet  
	Aufgabe: überprüft ob der Button gedrückt wird 
	Return: wenn der Button gedrückt wird gibt die Funktion true zurück ansonsten wird false zurück gegeben 
	*/
	bool ueberprueftButtonObGedruektWird(unsigned int ButtenID);

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
	inline void TextfeldHinzufuegen(const sf::Color farbe, const sf::Font &font, sf::Vector2f pos);
	
	
	/*
	Name: aktualisierenTextfelder
	param: sf::Event& event -> Speichert die Information welche Taste gedrückt wurde, sf::Vector2i MousPos -> Die aktuelle Mauszeiger Position 
	Aufgabe: Wenn es ein Textfeld gibt wird die Tasten information an Textfeld weitergereicht
	Retrun: keine
	*/
	void aktualisierenTextfelder(const sf::Event& event, const sf::Vector2i& MousPos);

	/*
	Name: ueberpruefenObEnterGedruekt
	param: sf::Event& event -> Speichert die Information welche Taste gedrückt wurde
	Aufgabe: Wenn es ein Textfeld gibt wird die Tasten information an Textfeld weitergereicht. Die Klasse überpruft ob enter gedruckt wurde das Ergebniss wird an ueberpruefenObEnterGedruekt zurück gegeben.
	Retrun: Wenn Textfeld vorhanden dann wird das Ergbniss weitergereicht ansonsten wird false zurück gegeben
	*/
	bool ueberpruefenObEnterGedruekt(const sf::Event& event);
	
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
	void neueAnzeige(std::string Text, unsigned PosTextY,
		unsigned IDTexture, unsigned PosTextureX, unsigned PosTextureY);

	/*
	Name: TextAendern
	param: std::string Text -> Der Text der Angezeigt werden soll, int PosTextY -> Die Position der Oberkante des Textes
	Aufgabe: Die Funktion überschreibt den Text der Kachel und die y - Koordinate des Textes 
	Retrun: keine
	*/
	void TextAendern(std::string Text, unsigned PosTextY);

	/*
	Name: aktualisierenPosition
	param: float Kachel_x -> Die neue X Koordienate der Kachel, float Kachle_y -> Die neue Y Koordienate der Kachel, float Kachel_Breite -> Die neue Breite der Kachel, float Kachel_Hohe -> Die neue Hohe der Kachel
	Aufgabe: Die Funktion überschreibt die Position und die Masse des Buttons
	Retrun: keinen
	*/
	void aktualisierenPosition(float Kachel_x, float Kachel_y, float Kachel_Breite, float Kachel_Hohe);
	
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
	bool MausSchwebtDrüber(const sf::Vector2i& mouspos);
	
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
	inline void setKachel_Gedrücktfarbe();

	/*
	Name: setKachel_Schwebefarbe
	param: keine
	Aufgabe: Die Funktion setzt die Farbe der Kachel auf die bei der Initzalisierung übergebene Schwebefarbe
	Retrun: keine
	*/
	inline void setKachel_Schwebefarbe();

	/*
	Name: setKachel_Hintergrundfarbe
	param: keine
	Aufgabe: Die Funktion setzt die Farbe der Kachel auf die bei der Initzalisierung übergebene Hintergrundfarbe
	Retrun: keine
	*/
	inline void setKachel_Hintergrundfarbe();

	//--------------------------------Get/Set----------------------------------------------//

	/*
	Name: setGroese
	param: sf::Vector2f posKachel -> Die neue Position der Kachel, sf::Vector2f posTex -> Die neue Position des Kacheltextes, sf::Vector2f size -> Die neue Größe der Kachel
	Aufgabe: Die Funktion gibt die bei der Initizalisierung übergeben ID zurück
	Retrun: keine
	*/
	void setGroese(sf::Vector2f posKachel, sf::Vector2f posTex, sf::Vector2f size);

	/*
	Name: setTextureGroessenSkalierungsFaktor
	param: float sice -> Den neuen Skalierungs Faktor mit dem das Texture vergrößert wird
	Aufgabe: Die Funktion speichert den Übergebenen Faktor
	Retrun: keine
	*/
	inline void setTextureGroessenSkalierungsFaktor(float sice);
	
	/*
	Name: getTextureID
	param: keine
	Aufgabe: Die Funktion gibt die bei der Initizalisierung übergeben ID des Textures zurück
	Retrun: Die ID des Texture als int
	*/
	const inline unsigned int getTextureID() const;

	/*
	Name: getTextureGroessenSkalierungsFaktor
	param: keine
	Aufgabe: Die Funktion gibt die aktuelle Größen Skalierung des Textures zurück 
	Retrun: Die aktuelle Größe als float
	*/
	const inline float getTextureGroessenSkalierungsFaktor() const;
	
	/*
	Name: getTexturePosition
	param: keine
	Aufgabe: Die Funktion gibt die Koordinaten des Textures zurück
	Retrun: Die Koordinaten als sf::Vector2f
	*/
	const inline sf::Vector2f getTexturePosition() const;

	/*
	Name: setTexturePosition
	param: sf::Vector2f pos -> Die neuen Koordinaten des Textures
	Aufgabe: Die Funktion speichert die neuen Koordinaten des Textures
	Retrun: keine
	*/
	void inline setTexturePosition(sf::Vector2f pos);
	
	/*
	Name: getID
	param: keine
	Aufgabe: Die Funktion gibt die bei der Initizalisierung übergeben ID zurück
	Retrun: Die ID der Kachel als int
	*/
	const inline unsigned int getID() const;

	/*
	Name: getPosition
	param: keine
	Aufgabe: Die Funktion gibt die Position der Kachel zurück
	Retrun: Die Funktion gibt die Positon als sf::Vector2f zurück
	*/
	const inline sf::Vector2f getPosition() const;

	/*
	Name: getGroese
	param: keine
	Aufgabe: Die Funktion gibt die Hohe und Breite der Kachel zurück
	Retrun: Die Funktion gibt die Hohe und Breite als sf::Vector2f zurück
	*/
	const inline sf::Vector2f getGroese() const;

	private:

	/*---------------------------------Kachel Variablen--------------------------------------------*/

	// Die Variable speichert die Größe, die aktuelle Farbe, die Position und wird auf das Spiel window gemalt
	sf::RectangleShape sf_rsKachel;

	//Die Variable speichert den Text der Kachel, die Position des Textes, den Font und die Textfarbe und wird auf das Spiel window gemalt
	sf::Text sf_tText;

	//Die Variablen speichern die Farbwerte welche die Kachel in den entsprechenden Fallen annimmt. Wird in den Farben set Funktionen verwendet.
	sf::Color sf_cHintergrundfarbe, sf_cSchwebefarbe, sf_cGedrücktfarbe;

	//Speichert die ID der Kachel welche die Game Klasse für die Zuordnung der Hauptmenu auswahl braucht und für Bereichseingrenzung an manchen stellen 
	unsigned int iID;

	//Die Variable speichert ob die Kachel gedrückt wurde um unbeabsichtigtes drücken zu verhindern 
	bool bDruecken;

	//Die Variable speichert wie lange die gedrückt Farbe angezeigt werden soll. Die Variable fungiert wie eine art Timer, damit der User sieht, dass das System das drücken Registriert hat. 
	unsigned int iVerbleibendeDrueckZeit;

	//Die Funktion setzt den neuen Text und die Y-Koordinate des Textes und berrechnet die X Koordinate 
	void newText(std::string Text, unsigned int PosTextY);
	//int NormalPos;
	
	/*-------------------------------------Texture Variablen----------------------------------------*/
	
	//Speichert die ID des Texture welche die View Klasse für die Zuordnung der Texture braucht Hauptmenu auswahl braucht und für Bereichseingrenzung an manchen stellen 
	unsigned iIDTexture;

	//Speichert die Position des Textures damit View das Texture an der Richtige stelle anzeigt 
	sf::Vector2f TexturePosition;

	//Die Variable speichert den Größenfaktor mit dem View die Bildgröße ändert 
	float TextureGroessenSkalierungsFaktor;

	/*-------------------------------------Butto Variablen----------------------------------------*/

	//Speichert alle Button die die Kachel hat  
	std::unordered_map<unsigned, Button*> umButton;

	/*-------------------------------------Textfeld Variablen----------------------------------------*/
	//Der Pointer Speichert die Adreese des Textfeldes wenn ein Textfeld benötigt wird ansonsten ist er auf Nullptr
	//Textfeld* cTextfeld;
};

