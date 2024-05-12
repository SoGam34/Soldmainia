#include "Data.h"

Data::Data()
{
	Einheiten.clear();
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

int Data::getMONATS_DAUER() const
{
	return MONATS_DAUER;
}

float Data::getTagesDauer()
{
	return TagesDauer;
}

void Data::setTagesDauer(float neueDauer)
{
	TagesDauer = neueDauer;
}
