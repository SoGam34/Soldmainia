#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <vector>
#include <iostream>
#include <time.h>
#include <sstream>
#include <mutex>
#include <memory>
#include <thread>
#include <optional>
#include <unordered_map>

#include "Timer.h"
#include "Butten.h"
#include "Textfeld.h"
#include "Kachel.h"

class Animationen
{
public:
	Animationen()=delete;
	Animationen(sf::Font font);
	~Animationen();

	void Aktualisieren(sf::Vector2i vMauspos);

	void draw(sf::RenderTarget* window);

	void startUpgradeAnimation(int Spalte, int breite, int hohe);

	void startBenarichtigung(bool gut, std::string Text);
	
	void clearWindow(sf::RenderTarget* window);

	void setFont(sf::Font* font);

	void KeinGeld(sf::Vector2f Pos, sf::Font* font);

	void KeineBerechtigung(sf::Vector2f Pos, sf::Font* font);

	bool getKeineBenarichtigung();

	void updateKachelPos(int PosX, int PosY, int Breite, int Hohe);

private:
	sf::Texture UpgradePfeil;
	std::vector<sf::Sprite> Pfeile;
	Kachel* kBenarichtigung;
	sf::Text sfBenarichtigungsText;

	bool bKeinBenarichtigung;

	int sBenarichtigung, sUpgradeAnimation;
	bool bBenarichtigungsArt;
	int r, g, b;
};

