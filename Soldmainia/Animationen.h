#pragma once
#include "pch.h"

class Animationen
{
public:
	Animationen();
	~Animationen();

	void Aktualisieren();

	void draw(sf::RenderTarget* window);

	void startUpgradeAnimation(int Spalte);

	void startBenarichtigung(bool gut);
	
	void clearWindow(sf::RenderTarget* window);

private:
	sf::Texture UpgradePfeil;
	std::vector<sf::Sprite> Pfeile;

	int sBenarichtigung, sUpgradeAnimation;
	bool bBenarichtigungsArt;
	int r, g, b;
};

