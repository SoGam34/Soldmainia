#include "PreHeader.h"
#include "View.h"

View::View(std::shared_ptr<Data> data, std::mutex& mutex)
{
	window = new sf::RenderWindow(sf::VideoMode(1020, 500), "Soldmainia", sf::Style::Resize | sf::Style::Close);
	window->setFramerateLimit(26);

	cData = data;
	
	tTexture.loadFromFile(Addressen[0]);
	sSprite.setTexture(tTexture);

	sfText.setPosition(20, 10);
	sfText.setCharacterSize(20);

	std::lock_guard<std::mutex> lock(mutex);
	sfText.setFont(*cData->getFont());

	cData->setWindowSize(static_cast<sf::Vector2f>(window->getSize()));
}

View::~View()
{
	delete window;
}

void View::DrawHauptmenu(int iTage)
{
	cData->getAnimationen().clearWindow(window);
	drawSprite(0, 8);
	drawText(0, 8, "Hauptmenue", iTage);
	cData->getAnimationen().draw(*window);
	window->display();
}

void View::DrawBAZ(int iTage)
{
	cData->getAnimationen().clearWindow(window);
	drawFenster(8, 4);
	drawSprite(8, 4);
	drawText(8, 4, "BAZ", iTage);
	cData->getAnimationen().draw(*window);
	window->display();
}

void View::DrawScoutbuero(int iTage)
{
	cData->getAnimationen().clearWindow(window);
	drawFenster(12, 4);
	drawSprite(12, 4);
	cData->getAnimationen().draw(*window);
	drawText(12, 4, "Scout Buero", iTage);
	window->display();
}

void View::DrawNichtVerfuegbar()
{
	cData->getAnimationen().clearWindow(window);
	sf::Text Warnung;
	Warnung.setFont(*cData->getFont());
	Warnung.setPosition(window->getPosition().x / 2 - 20, window->getPosition().y / 2);
	Warnung.setCharacterSize(30);
	Warnung.setString("Dieses Menu ist zur Zeit nicht Verfuegbar");
	window->draw(Warnung);
	window->display();
}

void View::DrawTraningszentrum(int iTage)
{
		cData->getAnimationen().clearWindow(window);
		drawFenster(16, 4);
		drawSprite(16, 4);
		cData->getAnimationen().draw(*window);
		drawText(16, 4, "Trainingszentrum", iTage);
		window->display();
}

void View::DrawErholungsresort(int iTage)
{
	cData->getAnimationen().clearWindow(window);
	drawFenster(24, 4);
	drawSprite(24, 4);
	cData->getAnimationen().draw(*window);
	drawText(24, 4, "Erholungsresort", iTage);
	window->display();
}

void View::DrawDiffrent(Traningszentrum& e)
{
	cData->getAnimationen().clearWindow(window);
	e.Mahlen(*window);
	cData->getAnimationen().draw(*window);
	window->display();
}

void View::DrawDiffrent(Erholungsresort& e)
{
	cData->getAnimationen().clearWindow(window);
	e.Mahlen(*window);
	cData->getAnimationen().draw(*window);
	window->display();
}

sf::Vector2i View::getMousPos()
{
	return sf::Mouse::getPosition(*window);
}

sf::RenderWindow& View::getWindow()
{
	return *window;
}

void View::ReSize()
{
	cData->setBreite((window->getSize().x -100)/ 4);
	cData->setHohe((window->getSize().y - 30 - 70) / 2);
	cData->setWindowSize(static_cast<sf::Vector2f>(window->getSize()));

	int temp=0;
	for (int i = 0; i < 16; i++)
	{
		if (temp % 4 == 0)
			temp = 0;

		if (i > 7)
		{
			cData->getKacheln(i).aktualisierenPosition((temp * cData->getBreite() + (temp + 1) * 20), 70, cData->getBreite(), 2 * cData->getHohe() + 20);	//1 * iBreite + 2 * iAbstandthalter+15
		}

		else
		{
			if (i < 4)
				cData->getKacheln(i).aktualisierenPosition(temp * cData->getBreite() + (temp + 1) * 20 + 15, 70, cData->getBreite(), cData->getHohe());

			else if (i < 8&&i>3)
				cData->getKacheln(i).aktualisierenPosition(temp * cData->getBreite() + (temp + 1) * 20 + 15, 90 + cData->getHohe(), cData->getBreite(), cData->getHohe());
		}
		temp++;
	}

	cData->getAnimationen().updateKachelPos(static_cast<int>(1.5 * cData->getBreite()), 70, cData->getBreite(), cData->getHohe());
	
}

void View::drawFenster(int start, int range)
{
	for (int i = start; i < start + range; i++)
	{
		cData->getKacheln(i).drawFenster(*window);
	}
}

void View::drawSprite(int start, int range)
{
	for (int i = start; i < start + range; i++)
	{
		if (cData->getKacheln(i).getTextureID() != 99)
		{
			tTexture.loadFromFile(Addressen[cData->getKacheln(i).getTextureID()]);
			sSprite.setTexture(tTexture);
			sSprite.setPosition(cData->getKacheln(i).getTexturePosition());

			sSprite.setTextureRect(sf::IntRect(0, 0, 200, 200));
			sSprite.setScale(static_cast<float>(cData->getBreite() / 200) + (cData->getKacheln(i).getTextureGroessenSkalierungsFaktor() - 1), static_cast<float>(cData->getHohe() / 200)+(cData->getKacheln(i).getTextureGroessenSkalierungsFaktor() - 1));
			
			window->draw(sSprite);
		}
	}
}

void View::drawText(int start, int range, std::string titel, int iTag)
{
	std::stringstream ssTitel;
	float temp = 20;
		
	ssTitel << "Kontostand: " << cData->getiKontostand();
	sfText.setString(ssTitel.str());
	sfText.setPosition(temp, sfText.getPosition().y);
	window->draw(sfText);
	
	ssTitel.str("");
	ssTitel<< titel;
	temp = static_cast<float>(window->getSize().x) * 0.45;
	sfText.setString(ssTitel.str());
	sfText.setPosition(temp, sfText.getPosition().y);
	window->draw(sfText);
	
	ssTitel.str("");
	ssTitel  << "Tag: " << iTag;
	temp = static_cast<float>(window->getSize().x) * 0.9;
	sfText.setString(ssTitel.str());
	sfText.setPosition(temp, sfText.getPosition().y);
	window->draw(sfText);

	for (int i = start; i < start + range; i++)
	{
		cData->getKacheln(i).drawText(*window);
	}
}
