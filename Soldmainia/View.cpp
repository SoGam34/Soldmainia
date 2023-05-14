#include "View.h"

View::View(std::shared_ptr<Data> data, std::mutex& mutex)
{
	window = new sf::RenderWindow(sf::VideoMode(1020, 500), "Soldmainia");
	window->setFramerateLimit(25);
	
	cData = data;
	
	tTexture.loadFromFile(Addressen[0]);
	sSprite.setTexture(tTexture);

	sfText.setPosition(20, 10);
	sfText.setCharacterSize(20);

	std::lock_guard<std::mutex> lock(mutex);
	sfText.setFont(*cData->getFont());
}

View::~View()
{
	delete window;
}

void View::DrawHauptmenu(int iTage)
{
	cData->getAnimationen().clearWindow(window);
	drawFenster(0, 8);
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
	cData->getAnimationen().draw(window);
	drawText(8, 4, "BAZ", iTage);
	window->display();
}

void View::DrawScoutbuero(int iTage)
{
	cData->getAnimationen().clearWindow(window);
	drawFenster(12, 4);
	drawSprite(12, 4);
	cData->getAnimationen().draw(window);
	drawText(12, 4, "Scoutbüro", iTage);
	window->display();
}

void View::DrawTraningszentrum(int iTage)
{
		cData->getAnimationen().clearWindow(window);
		drawFenster(16, 4);
		drawSprite(16, 4);
		cData->getAnimationen().draw(window);
		drawText(16, 4, "Traingszentrum", iTage);
		window->display();
}

void View::DrawErholungsresort(int iTage)
{
	cData->getAnimationen().clearWindow(window);
	drawFenster(24, 4);
	drawSprite(24, 4);
	cData->getAnimationen().draw(window);
	drawText(24, 4, "Erholungsresort", iTage);
	window->display();
}

void View::DrawDiffrent(Traningszentrum& e)
{
	cData->getAnimationen().clearWindow(window);
	e.Mahlen(*window);
	cData->getAnimationen().draw(window);
	window->display();
}

void View::DrawDiffrent(Erholungsresort& e)
{
	cData->getAnimationen().clearWindow(window);
	e.Mahlen(*window);
	cData->getAnimationen().draw(window);
	window->display();
}

sf::Vector2i View::getMousPos()
{
	return sf::Mouse::getPosition(*window);
}

bool View::windowOpen()
{
	return window->isOpen();
}

void View::Close()
{
	window->close();
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
			sSprite.setTextureRect(sf::IntRect(0, 0, 200 , 200 * cData->getKacheln(i).getScale()));
			sSprite.setScale(cData->getKacheln(i).getScale(), cData->getKacheln(i).getScale());
			window->draw(sSprite);
		}
	}
}

void View::drawText(int start, int range, std::string titel, int iTag)
{
	std::stringstream ssTitel;
	ssTitel << "Kontostand: " << cData->getiKontostand() << "                         " << titel << "                      Tag: " << iTag;
	sfText.setString(ssTitel.str());
	window->draw(sfText);

	for (int i = start; i < start + range; i++)
	{
		cData->getKacheln(i).drawText(*window);
	}
}
