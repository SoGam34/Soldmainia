#pragma once
#include "Data.h"

class View 
{
public:
	//De/Konstrucktor
	View();
	View(Data* data);
	~View();
	
	void DrawHauptmenu(int iTage);
	void DrawBAZ(int iTage);
	void DrawScoutbuero(int iTage);
	void DrawTraningszentrum(int iTage);
	void DrawErholungsresort(int iTage);

	sf::Vector2i getMousPos();
	bool windowOpen();
	void Close();
	sf::RenderWindow& Window()
	{
		return *window;
	}

private:
	void drawFenster(int start, int range);
	void drawSprite(int start, int range);
	void drawText(int start, int range, std::string titel, int iTag);
	
	//window
	sf::RenderWindow* window;

	// Data zeiger
	Data* cData;				 
	
	sf::Texture tTexture;
	sf::Sprite sSprite;
	
	std::string Addressen[16]
	{
		"Texturen/Pfeil.png",
		"Texturen/Haken.png",
		"Texturen/AktiveAuftrage2.png",
		"Texturen/Auftrage.png",
		"Texturen/ArbeitBeschleunigen.png",
		"Texturen/BessereRang.png",
		"Texturen/ErhohungGrundstarke.png",
		"Texturen/Erholungsresort.png",
		"Texturen/Kaserne.png",
		"Texturen/Logistik System.png",
		"Texturen/Scoutbüro.png",
		"Texturen/Tranigszentrum.png",
		"Texturen/WarteAusbildung.png",
		"Texturen/WarteScoutbüro.png",
		"Texturen/WenigerKosten.png",
		"Texturen/Zentrale.png"
	};
	sf::Text sfText;
};