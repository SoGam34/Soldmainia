#include "View.h"

View::View()
{
	window = new sf::RenderWindow(sf::VideoMode(1020, 500), "Soldmainia", sf::Style::Resize | sf::Style::Close);
	window->setFramerateLimit(25);
	
	cData = nullptr;
	
	tTexture.loadFromFile(Addressen[0]);
	sSprite.setTexture(tTexture);

	sfText.setPosition(20, 10);
	sfText.setCharacterSize(20);
	sfText.setFont(*cData->getFont());
}

View::View(Data* data)
{
	window = new sf::RenderWindow(sf::VideoMode(1020, 500), "Soldmainia");
	window->setFramerateLimit(25);
	
	cData = data;
	
	tTexture.loadFromFile(Addressen[0]);
	sSprite.setTexture(tTexture);

	sfText.setPosition(20, 10);
	sfText.setCharacterSize(20);
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
	drawText(0, 8, "Hauptmenu", iTage);
	cData->getAnimationen().draw(window);
	window->display();
}

void View::DrawBAZ(int iTage)
{
	cData->getAnimationen().clearWindow(window);
	drawFenster(8, 4);
	drawSprite(8, 4);
	drawText(8, 4, "BAZ", iTage);
	cData->getAnimationen().draw(window);
	window->display();
}

void View::DrawScoutbuero(int iTage)
{
	cData->getAnimationen().clearWindow(window);
	drawFenster(12, 4);
	drawSprite(12, 4);
	cData->getAnimationen().draw(window);
	drawText(12, 4, "Scoutb�ro", iTage);
	window->display();
}

void View::DrawNichtVerf�gbar()
{
	cData->getAnimationen().clearWindow(window);
	sf::Text Warnung;
	Warnung.setFont(*cData->getFont());
	Warnung.setPosition(window->getPosition().x / 2 - 20, window->getPosition().y / 2);
	Warnung.setCharacterSize(30);
	Warnung.setString("Dieses Menu ist zur Zeit nicht Verf�gbar");
	window->draw(Warnung);
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

	int temp=0;
	for (int i = 0; i < 16; i++)
	{
		if (temp == 4)
			temp = 0;

			if (i > 7)
			{
				cData->getKacheln(i).updatePos((temp * cData->getBreite()+(temp+1)*20), 70, cData->getBreite(), 2 * cData->getHohe() + 20);	//1 * iBreite + 2 * iAbstandthalter+15
			}

			else
				if(i<4)
				cData->getKacheln(i).updatePos(temp * cData->getBreite() + (temp+1) * 20 + 15, 70, cData->getBreite(), cData->getHohe());
				
				else if(i<8)
					cData->getKacheln(i).updatePos(temp * cData->getBreite() + (temp+1) * 20 + 15, 90+cData->getHohe(), cData->getBreite(), cData->getHohe());
		

			temp++;
	}

	cData->setWindowSize(static_cast<sf::Vector2f>(window->getSize()));
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
			sSprite.setScale((cData->getBreite() / 200), cData->getHohe() / 200);
			
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
