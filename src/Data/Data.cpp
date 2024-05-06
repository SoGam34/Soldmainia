#include "Data.h"

Data::Data()
{
	Einheiten.clear();

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

std::vector<Einheit>& Data::getEinheiten()
{
	return Einheiten;
}

void Data::addEinheit(const Einheit &e)
{
	Einheiten.emplace_back(e);
}

unsigned int Data::getBekanntheit()
{
	return Bekantheit;
}

void Data::setBekanntheit(unsigned int value)
{
	Bekantheit = value;
}

int Data::getKontostand()
{
	return Kontostand;
}

void Data::abziehnVonKontostand(int betrag)
{
	Kontostand -= betrag;
}

void Data::hinzufuegenZuKontostand(int betrag)
{
	Kontostand += betrag;
}

void Data::erhoheAnzahlTage()
{
	AnzahlTage++;
}

int Data::getAnzahlTage()
{
	return AnzahlTage;
}

const int Data::getMONATS_DAUER() const
{
	return MONATS_DAUER;
}

bool Data::getImEinheitsAuswahlMenu()
{
	return ImEinheitsAuswahlMenu;
}

void Data::setEinheitsAuswahlMenu(bool neuerStatus)
{
	ImEinheitsAuswahlMenu = neuerStatus;
}

float Data::getTagesDauer()
{
	return TagesDauer;
}

void Data::setTagesDauer(float neueDauer)
{
	TagesDauer = neueDauer;
}
