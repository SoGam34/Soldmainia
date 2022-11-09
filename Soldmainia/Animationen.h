#pragma once
#include "pch.h"

class Animationen
{
public:
	Animationen();
	~Animationen();

	void Aktualisieren(sf::RenderTarget* window);

	void draw(sf::RenderWindow* window);

	void startUpgradeAnimation(int Spalte);

	void startBenarichtigung(bool gut);

private:
	sf::Texture UpgradePfeil;
	std::vector<sf::Sprite> Pfeile;

	int sBenarichtigung, sUpgradeAnimation;
	bool bBenarichtigungsArt;
	int r, g, b;
};

