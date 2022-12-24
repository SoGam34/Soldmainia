#pragma once

#include <SFML/Graphics.hpp>

class Animationen
{
public:

	Animationen();
	Animationen(sf::Font font);
	~Animationen();

	void Aktualisieren();

	void draw(sf::RenderTarget* window);

	void startUpgradeAnimation(int Spalte, int breite, int hohe);

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

