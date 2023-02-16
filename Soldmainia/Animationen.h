#pragma once
#include "pch.h"

class Animationen
{
public:

	Animationen(sf::Font font);
	~Animationen();

	void Aktualisieren();

	void draw(sf::RenderTarget* window);

	void startUpgradeAnimation(int Spalte);

	void startBenarichtigung(bool gut, std::string Text);
	
	void clearWindow(sf::RenderTarget* window);

	void setFont(sf::Font* font);

private:
	sf::Texture UpgradePfeil;
	std::vector<sf::Sprite> Pfeile;

	sf::Text sfBenarichtigungsText;

	int sBenarichtigung, sUpgradeAnimation;
	bool bBenarichtigungsArt;
	int r, g, b;
};

