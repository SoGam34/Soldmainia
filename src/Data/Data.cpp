#include "Data.h"

	Data::Data()
	{
		cAnimationen =  new Animationen(sfFont);
		WindowSize.x = 1020;
		WindowSize.y = 500;

		sfFont.loadFromFile("Texturen/ArialCEMTBlack.ttf");

		//BAZ
		aKacheln[11].ButtonHinzufuegen(3 * iAbstandthalter + 3 * iBreite + 35, 2 * iHohe + 50, 200, 30, 4, "Upgrade", sfFont, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255, 150, 0), sf::Color::White, aKacheln[11].getGroese().x, aKacheln[11].getGroese().y);
		aKacheln[10].ButtonHinzufuegen(2 * iAbstandthalter + 2 * iBreite + 35, 2 * iHohe + 50, 200, 30, 3, "Upgrade", sfFont, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255, 150, 0), sf::Color::White, aKacheln[10].getGroese().x, aKacheln[10].getGroese().y);
		aKacheln[9].ButtonHinzufuegen(1 * iAbstandthalter + 1 * iBreite + 35, 2 * iHohe + 50, 200, 30, 2, "Upgrade", sfFont, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255, 150, 0), sf::Color::White, aKacheln[9].getGroese().x, aKacheln[9].getGroese().y);
		aKacheln[8].ButtonHinzufuegen(15 + iAbstandthalter, 2 * iHohe + 50, 200, 30, 1, "Starten", sfFont, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255, 150, 0), sf::Color::White, aKacheln[8].getGroese().x, aKacheln[8].getGroese().y);
		aKacheln[8].ButtonHinzufuegen(35, 350, 200, 30, 11, "Mehr Mitglieder", sfFont, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255, 150, 0), sf::Color::White, aKacheln[8].getGroese().x, aKacheln[8].getGroese().y);
		aKacheln[8].ButtonHinzufuegen(35, 400, 200, 30, 12, "Weniger Mitglieder", sfFont, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255, 150, 0), sf::Color::White, aKacheln[8].getGroese().x, aKacheln[8].getGroese().y);

		//Scoutbuero
		aKacheln[12].ButtonHinzufuegen(35, 450, 200, 30, 1, "Starten", sfFont, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255, 150, 0), sf::Color::White, aKacheln[12].getGroese().x, aKacheln[12].getGroese().y);
		aKacheln[13].ButtonHinzufuegen(1 * iAbstandthalter + 1 * iBreite + 35, 450, 200, 30, 2, "Upgrade", sfFont, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255, 150, 0), sf::Color::White, aKacheln[13].getGroese().x, aKacheln[13].getGroese().y);
		aKacheln[14].ButtonHinzufuegen(2 * iAbstandthalter + 2 * iBreite + 35, 450, 200, 30, 3, "Upgrade", sfFont, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255, 150, 0), sf::Color::White, aKacheln[14].getGroese().x, aKacheln[14].getGroese().y);
		aKacheln[15].ButtonHinzufuegen(3 * iAbstandthalter + 3 * iBreite + 35, 450, 200, 30, 4, "Upgrade", sfFont, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255, 150, 0), sf::Color::White, aKacheln[15].getGroese().x, aKacheln[15].getGroese().y);

		//Trainingszentrum 
		aKacheln[16].ButtonHinzufuegen(45, 450, 200, 30, 5, "Lange Tranings Einheit", sfFont, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White, aKacheln[16].getGroese().x, aKacheln[16].getGroese().y);
		aKacheln[16].ButtonHinzufuegen(45, 350, 200, 30, 6, "Kurze Trainings Einheit", sfFont, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White, aKacheln[16].getGroese().x, aKacheln[16].getGroese().y);
		aKacheln[16].ButtonHinzufuegen(45, 400, 200, 30, 7, "Mittlere trainings Einheit", sfFont, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White, aKacheln[16].getGroese().x, aKacheln[16].getGroese().y);
		aKacheln[17].ButtonHinzufuegen(1 * iAbstandthalter + 1 * iBreite + 45, 450, 200, 30, 2, "Upgrade", sfFont, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White, aKacheln[17].getGroese().x, aKacheln[17].getGroese().y);
		aKacheln[18].ButtonHinzufuegen(2 * iAbstandthalter + 2 * iBreite + 45, 450, 200, 30, 3, "Upgrade", sfFont, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White, aKacheln[18].getGroese().x, aKacheln[18].getGroese().y);
		aKacheln[19].ButtonHinzufuegen(3 * iAbstandthalter + 3 * iBreite + 45, 450, 200, 30, 4, "Upgrade", sfFont, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White, aKacheln[19].getGroese().x, aKacheln[19].getGroese().y);

		//Trainingszentrum 
		aKacheln[24].ButtonHinzufuegen(45, 450, 200, 30, 5, "Erholung starten", sfFont, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White, aKacheln[24].getGroese().x, aKacheln[24].getGroese().y);
		aKacheln[25].ButtonHinzufuegen(1 * iAbstandthalter + 1 * iBreite + 45, 450, 200, 30, 2, "Upgrade", sfFont, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White, aKacheln[25].getGroese().x, aKacheln[25].getGroese().y);
		aKacheln[26].ButtonHinzufuegen(2 * iAbstandthalter + 2 * iBreite + 45, 450, 200, 30, 3, "Upgrade", sfFont, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White, aKacheln[26].getGroese().x, aKacheln[26].getGroese().y);
		aKacheln[27].ButtonHinzufuegen(3 * iAbstandthalter + 3 * iBreite + 45, 450, 200, 30, 4, "Upgrade", sfFont, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White, aKacheln[27].getGroese().x, aKacheln[27].getGroese().y);

		umEinheiten.clear();

		Einheit e("Kai");
		Einheit r("Alina");
		Einheit d("Samantha");
		Einheit f("Lars");
		Einheit g("Tina");
		addEinheit(e);
		addEinheit(r);
		addEinheit(d);
		addEinheit(f);
		addEinheit(g);
	}
	Data::~Data()
	{

	}

	Kachel& Data::getHauptmenu(int pos)
	{
		return aKacheln[pos];
	}

	Kachel& Data::getKacheln(int pos)
	{
		return aKacheln[pos];
	}

	Animationen& Data::getAnimationen()
	{
		return *cAnimationen;
	}

	std::vector<Einheit>& Data::getEinheiten()
	{
		return umEinheiten;
	}

	const void Data::addEinheit(const Einheit& const e)
	{
		umEinheiten.emplace_back(e);
	}

	unsigned int Data::getBekanntheit()
	{
		return iBekanntheit;
	}

	void Data::setBekanntheit(unsigned int value)
	{
		iBekanntheit = value;
	}

	sf::Font* Data::getFont()
	{
		return &sfFont;
	}

	int Data::getiKontostand()
	{
		return iKontostand;
	}

	void Data::setiKontostand(int kontostand)
	{
		iKontostand = kontostand;
	}

	void Data::setBenarichtigungAktiv()
	{
		bBenarichtigungAktiv = true;
	}

	bool Data::getBenarichtigungAktiv()
	{
		return bBenarichtigungAktiv;
	}

	int Data::getBreite()
	{
		return iBreite;
	}

	void Data::setBreite(int value)
	{
		iBreite = value;
	}

	int Data::getHohe()
	{
		return iHohe;
	}

	void Data::setHohe(int value)
	{
		iHohe = value;
	}

	sf::Vector2f Data::getWindowSize()
	{
		return WindowSize;
	}

	void Data::setWindowSize(sf::Vector2f windowsize)
	{
		WindowSize = windowsize;
	}