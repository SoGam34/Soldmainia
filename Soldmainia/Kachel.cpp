#include "PreHeader.h"
#include "Kachel.h"
//Konstruktoren#include "stdafx.h"

Kachel::Kachel(std::string Text, int PosTextY, sf::Color TextColor, sf::Font& font,
	int IDTexture, int PosTextureX, int PosTextureY,
	int ID, int PosKachelX, int PosKachelY, float with, float height,
	sf::Color backroundColor, sf::Color hoverColor, sf::Color pressColor)
	: iIDTexture(IDTexture),
	TexturePosition(PosTextureX, PosTextureY),
	iID(ID),
	sf_cHintergrundfarbe(backroundColor),
	sf_cSchwebefarbe(hoverColor),
	sf_cGedruecktfarbe(pressColor),
	bDruecken(false),
	iVerbleibendeDrueckZeit(0)
{
	//Kachel	
	sf_rsKachel.setPosition(PosKachelX, PosKachelY);
	sf_rsKachel.setSize(sf::Vector2f(with, height));
	sf_rsKachel.setFillColor(sf_cHintergrundfarbe);
		
	// Text
	sf_tText.setCharacterSize(15);
	sf_tText.setFont(font);
	sf_tText.setFillColor(TextColor);
	newText(Text, PosTextY);

	//Butten
	umButton.clear();

	//TextureGroessenSkalierungsFaktor = 1;
		
	//NormalPos = sf_tText.getPosition().y;

	//Textfeld
	//cTextfeld = nullptr;
}

Kachel::~Kachel()
{
	for (int i = 0; i < umButton.size();)
	{
		delete umButton[i];
		umButton.erase(i);
	}
	umButton.clear();
}
//Funktionen zum dieseignen und Mahlen der Kachel
inline void Kachel::ButtonHinzufuegen(float x, float y, float with, float heigth, int ID,
	std::string text, sf::Font& font,
	sf::Color backroundColor, sf::Color hoverColor, sf::Color PressColor, sf::Color textColor,
	float KachelBreite, float KachelHohe)
{
	std::pair<int, Button*> temp1((int)umButton.size(), new Button(x, y, with, heigth, ID, text, font, backroundColor, hoverColor, PressColor, textColor, KachelBreite, KachelHohe));
	umButton.insert(temp1);
}

inline void Kachel::TextfeldHinzufuegen(const sf::Color farbe, const sf::Font& font, sf::Vector2f pos)
 {
	// cTextfeld = new Textfeld(farbe, font, pos);
 }

void Kachel::neueAnzeige(std::string Text, unsigned PosTextY,
	unsigned IDTexture, unsigned PosTextureX, unsigned PosTextureY)
{
	for (int i = 0; i < umButton.size();)
	{
		delete umButton[i];
		umButton.erase(i);
	}

	//if (cTextfeld != nullptr)
	//	delete cTextfeld;
	//cTextfeld = nullptr;

	newText(Text, PosTextY);
	// Texture
	iIDTexture = IDTexture;
	TexturePosition.x = PosTextureX;
	TexturePosition.y = PosTextureY;
}

void Kachel::TextAendern(std::string Text, unsigned PosTextY)
{
	newText(Text, PosTextY);
}

void Kachel::drawFenster(sf::RenderTarget& target)
{
	target.draw(sf_rsKachel);
	for (auto &e : umButton)
		e.second->drawFenster(target);
}

void Kachel::drawText(sf::RenderTarget& target)
{
	target.draw(sf_tText);
	for (auto &e : umButton)
		e.second->drawText(target);

	//if (cTextfeld != nullptr)
	//	cTextfeld->drawText(target);
}

//textfeld
void Kachel::aktualisierenTextfelder(const sf::Event& event, const sf::Vector2i& MousPos)
{
	/*if (cTextfeld != nullptr)
	{
		if (cTextfeld->getPosition().x > MousPos.x && cTextfeld->getPosition().x + cTextfeld->getBegrenzungen().width < MousPos.x &&
			cTextfeld->getPosition().y >MousPos.y && cTextfeld->getPosition().y + cTextfeld->getBegrenzungen().height < MousPos.y)
			cTextfeld->setTextfeldAusgewahlt(true);

		cTextfeld->BuchstabeGedrueckt(event);
		
	}*/
}

bool Kachel::ueberpruefenObEnterGedruekt(const sf::Event& event)
{
	//if (cTextfeld != nullptr)
	//	return cTextfeld->ueberpruefeObEnterGedrueckt(event);

	return false;
}
bool Kachel::getTextfeldAusgewahltStatus()
{
	//if (cTextfeld != nullptr)
	//	return cTextfeld->getAusgewahlt();

	return false;
}

//Funktionen zum �berp�fen der Maus und �ndern der Farbe
	//Buttens
std::optional<unsigned int> Kachel::ueberprueftAlleButtonObMausSchwebtDrueber(const sf::Vector2i& mouspos)
{
	for (auto &e:umButton)
	{
		if (e.second->MausSchwebtDrueber(mouspos))
		{
			e.second->setButton_Schwebefarbe();
			return e.second->getID();
		}
	}
	return {};
}

bool Kachel::ueberprueftButtonObGedruektWird(unsigned int ButtenID)
{
	if (umButton[ButtenID]->wirdGedrueckt())
	{
		umButton[ButtenID]->setButton_Gedruecktfarbe();
		return true;
	}
	return false;
}

void Kachel::setAlleButtenAufHintergrundfarbe()
{
	for (auto &e : umButton)
		e.second->setButton_Hintergrundfarbe();
}

void Kachel::aktualisierenPosition(float Kachel_x, float Kachel_y, float Kachel_Breite, float Kachel_Hohe)
 {
	 int tempx = Kachel_x - sf_rsKachel.getPosition().x;
	 int tempy = Kachel_y - sf_rsKachel.getPosition().y;
	 int ButtenOffsetY = static_cast<int>((Kachel_Hohe - sf_rsKachel.getSize().y) + tempy);

	 TexturePosition += sf::Vector2f(tempx, tempy);

	 sf_rsKachel.setPosition(Kachel_x, Kachel_y);
	 sf_rsKachel.setSize(sf::Vector2f(Kachel_Breite, Kachel_Hohe));
	
	 for (auto &e : umButton)
		 e.second->aktualisierenPosition(tempx, ((ButtenOffsetY>0)?ButtenOffsetY-10:ButtenOffsetY+10), Kachel_Breite, Kachel_Hohe);

	 if (iID < 9)
		 sf_tText.setPosition(
			 sf_rsKachel.getPosition().x + ((sf_rsKachel.getGlobalBounds().width / 2) - (sf_tText.getGlobalBounds().width / 2)),
			 sf_rsKachel.getPosition().y + sf_rsKachel.getGlobalBounds().height * 0.91
		 );

	 else
	 {
		 if (iID == 9 || iID == 13)
			 sf_tText.setPosition(
				 sf_rsKachel.getPosition().x + ((sf_rsKachel.getGlobalBounds().width / 2) - (sf_tText.getGlobalBounds().width / 2)),
				 sf_rsKachel.getPosition().y + ((sf_rsKachel.getGlobalBounds().height * 2) / 3) - (sf_tText.getGlobalBounds().width / 2)
			 );
		 else
		 sf_tText.setPosition(
			 sf_rsKachel.getPosition().x + ((sf_rsKachel.getGlobalBounds().width / 2) - (sf_tText.getGlobalBounds().width / 2)),
			 sf_rsKachel.getPosition().y + ((sf_rsKachel.getGlobalBounds().height * 2) / 3)
		 );
	 }
}

 void Kachel::aktualisieren()
 {
	 if (iVerbleibendeDrueckZeit > 0)
		 iVerbleibendeDrueckZeit--;

	 if (iVerbleibendeDrueckZeit != 0)
		 sf_rsKachel.setFillColor(sf_cGedruecktfarbe);

	 for (auto &e : umButton)
		 e.second->aktualisieren();
 }

 //Kachel
 bool Kachel::MausSchwebtDrueber(const sf::Vector2i& mouspos)
{
	if (mouspos.x > sf_rsKachel.getPosition().x && mouspos.x<sf_rsKachel.getPosition().x + sf_rsKachel.getGlobalBounds().width &&
		mouspos.y>sf_rsKachel.getGlobalBounds().top && mouspos.y < sf_rsKachel.getGlobalBounds().top + sf_rsKachel.getGlobalBounds().height)
		return true;
	return false;
}

bool Kachel::wirdGedruedckt()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == true && bDruecken == false)
	{
		bDruecken = true;
		return true;
	}

	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		bDruecken = false;

	return false;
}

inline void Kachel::setKachel_Schwebefarbe()
{
	 if (iVerbleibendeDrueckZeit == 0)
	 {
		 sf_rsKachel.setFillColor(sf_cSchwebefarbe);
	 }
}

inline void Kachel::setKachel_Gedruecktfarbe()
{
	iVerbleibendeDrueckZeit = 12;
	sf_rsKachel.setFillColor(sf_cGedruecktfarbe);
}

inline void Kachel::setKachel_Hintergrundfarbe()
{
	 if (iVerbleibendeDrueckZeit == 0)
	 {
		 sf_rsKachel.setFillColor(sf_cHintergrundfarbe);
	 }
}
void Kachel::setGroese(sf::Vector2f posKachel, sf::Vector2f posTex, sf::Vector2f size)
 {
	 sf_rsKachel.setPosition(posKachel);
	 sf_rsKachel.setSize(size);
	 TexturePosition.x = posTex.x;
	 TexturePosition.y = posTex.y;
 }
 inline void Kachel::setTextureGroessenSkalierungsFaktor(float sice)
 {
	 TextureGroessenSkalierungsFaktor = sice;
 }
 const inline unsigned int Kachel::getID() const
 {
	 return iID;
 }
 const inline unsigned int Kachel::getTextureID() const
 {
	 return iIDTexture;
 }

 const inline float Kachel::getTextureGroessenSkalierungsFaktor() const
 {
	 return TextureGroessenSkalierungsFaktor;
 }

 const inline sf::Vector2f Kachel::getTexturePosition() const
 {
	 return TexturePosition;
 }

 void inline Kachel::setTexturePosition(sf::Vector2f pos)
 {
	TexturePosition=pos;
 }

 const inline sf::Vector2f Kachel::getPosition() const
 {
	 return sf_rsKachel.getPosition();
 }
 
 const inline sf::Vector2f Kachel::getGroese() const
 {
	 return sf_rsKachel.getSize();
 }

//Privat Functions
 void Kachel::newText(std::string Text, unsigned int PosTextY)
{
	sf_tText.setString(Text);
	sf_tText.setPosition(
		sf_rsKachel.getPosition().x + ((sf_rsKachel.getGlobalBounds().width / 2.f) - (sf_tText.getGlobalBounds().width / 2.f)),
		PosTextY
	);
}
