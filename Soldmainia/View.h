#pragma once
#include "Data.h"

class View 
{
public:
	//De/Konstrucktor
	View();
	View(Data* data);
	~View();
	
	void DrawHauptmenu();
	void DrawBAZ();
	void DrawScoutbüro();

private:
	void drawFenster(int start, int range);
	void drawSprite(int start, int range);
	void drawAnimation(int start, int range);
	void drawText(int start, int range);
	
	// Data zeiger
	Data* cData;				 
	
	sf::Texture tTexture;
	sf::Sprite sSprite;
	
	std::string Addressen[15];
};