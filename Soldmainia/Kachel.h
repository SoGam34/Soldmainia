#pragma once
#include "Textfeld.h"

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
	Name: neueAnzeige
	param: std::string Text -> Der Text der Angezeigt werden soll, int PosTextY -> Die Position der Oberkante des Textes, 
				int IDTexture -> Die Nummer des Textuers was Angezeigt werden soll, int PosTextureX -> Die X- Position des Texture , int PosTextureY -> Die Y-Position des Textures
	Aufgabe: Das Löschen aller Buttons und Textfelder und das überschreiben der modifizierbaren Eigenschaften der Kachel
	Retrun: keine
	*/
	void neueAnzeige(std::string Text, int PosTextY, 
				int IDTexture, int PosTextureX, int PosTextureY);

	/*
	Name: ButtonHinzufuegen
	param: alle die ein Button zur Initialisierung benötigt 
	Aufgabe: Anhangen eines neuen Button an den vButton Vektor 
	Retrun: keine
	*/
	void changeText(std::string Text, int PosTextY);
	
	/*
	Name: ButtonHinzufuegen
	param: alle die ein Button zur Initialisierung benötigt 
	Aufgabe: Anhangen eines neuen Button an den vButton Vektor 
	Retrun: keine
	*/
	int checkButtenishover(sf::Vector2i mouspos);

	/*
	Name: ButtonHinzufuegen
	param: alle die ein Button zur Initialisierung benötigt 
	Aufgabe: Anhangen eines neuen Button an den vButton Vektor 
	Retrun: keine
	*/
	bool checkButtenisPressed(int ButtenID, sf::Vector2i mouspos);

	/*
	Name: ButtonHinzufuegen
	param: alle die ein Button zur Initialisierung benötigt 
	Aufgabe: Anhangen eines neuen Button an den vButton Vektor 
	Retrun: keine
	*/
	void setButtenColorToNormal();

	/*
	Name: ButtonHinzufuegen
	param: alle die ein Button zur Initialisierung benötigt 
	Aufgabe: Anhangen eines neuen Button an den vButton Vektor 
	Retrun: keine
	*/
	void drawFenster(sf::RenderTarget& target);
	
	/*
	Name: ButtonHinzufuegen
	param: alle die ein Button zur Initialisierung benötigt 
	Aufgabe: Anhangen eines neuen Button an den vButton Vektor 
	Retrun: keine
	*/
	void drawText(sf::RenderTarget& target);

	//--------------------------------Textfeld Verwaltung----------------------------------------------//
	
	void addTextfeld(sf::Color farbe, sf::Font *font, sf::Vector2f pos);
	void updateTextfelder(sf::Event event, sf::Vector2i MousPos);

	bool EnterPress(sf::Event event);
	bool getTextfeldAusgewahltZustand();

	//--------------------------------Kachel Verwaltung----------------------------------------------//

	void updatePos(int PosX, int PosY, int breite, int hohe);
	
	void update();

	bool ishover(sf::Vector2i mouspos);

	bool isPressed(sf::Vector2i mouspos);
	
	
	//--------------------------------Kachel Farben----------------------------------------------//

	void sethoverColor();

	void setPressedColor();

	void setNormalColor();

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
	std::vector <Butten*> vButten;
	float TextureScale;

	//Textfeld
	Textfeld* cTextfeld;
};

