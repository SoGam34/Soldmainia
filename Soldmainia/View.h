#pragma once
#include "Data.h"
#include "Traningszentrum.h"
#include "Erholungsresort.h"

class View 
{
public:
	//De/Konstrucktor
	View() = delete;
	View(std::shared_ptr<Data> data, std::mutex& mutex);
	~View();
	
	void DrawHauptmenu(int iTage);
	void DrawBAZ(int iTage);
	void DrawScoutbuero(int iTage);
	void DrawNichtVerfuegbar();

	void DrawTraningszentrum(int iTage);
	void DrawErholungsresort(int iTage);

	void DrawDiffrent(Traningszentrum& e);
	void DrawDiffrent(Erholungsresort& e);

	void ReSize();

	void CheckWindow();
	sf::RenderWindow& getWindow();
	sf::Vector2i getMousPos();
	bool windowOpen();
	void Close();

private:
	void drawFenster(int start, int range);
	void drawSprite(int start, int range);
	void drawText(int start, int range, std::string titel, int iTag);
	
	//window
	sf::RenderWindow* window;
	

	// Data zeiger
	std::shared_ptr<Data> cData;
	
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
		"Texturen/Scoutb�ro.png",
		"Texturen/Tranigszentrum.png",
		"Texturen/WarteAusbildung.png",
		"Texturen/WarteScoutb�ro.png",
		"Texturen/WenigerKosten.png",
		"Texturen/Zentrale.png"
	};
	sf::Text sfText;
};