#include "Data.h"
#include <nlohmann/json.hpp>

Data::Data()
{
	Members.clear();

	// std::ifstream file("savegame.json");
	// nlohmann::json data;
	// file >> data;

	// Kontostand = data["Kontostand"];
	// AnzahlTage = data["AnzahlTage"];
	// TagesDauer = data["TagesDauer"];
	// Bekantheit = data["Bekantheit"];
	// TODO(Data): Einlesen der Inforationen
}

std::vector<std::variant<Battilion, Einzelkampfer>>& Data::getMembers()
{
	return Members;
}

void Data::addBattiliion(const Battilion& e)
{
	Members.emplace_back(e);
}

void Data::addEinzelkampfer(const Einzelkampfer& e)
{
	Members.emplace_back(e);
}

unsigned int Data::getBekanntheit() const
{
	return Bekantheit;
}

void Data::setBekanntheit(unsigned int const value)
{
	Bekantheit = value;
}

float Data::getKontostand() const
{
	return Kontostand;
}

void Data::abziehnVonKontostand(float const betrag)
{
	Kontostand -= betrag;
}

void Data::hinzufuegenZuKontostand(float const betrag)
{
	Kontostand += betrag;
}

void Data::erhoheAnzahlTage()
{
	AnzahlTage++;
}

int Data::getAnzahlTage() const
{
	return AnzahlTage;
}

int Data::getMONATS_DAUER() const
{
	return MONATS_DAUER;
}

double Data::getTagesDauer() const
{
	return TagesDauer;
}

void Data::setTagesDauer(float const neueDauer)
{
	TagesDauer = neueDauer;
}

void Data::saveGameToFile()
{
	// nlohmann::json data ={"Kontostand", Kontostand},
	//		       {"AnzahlTage", AnzahlTage},
	//		       {"TagesDauer", TagesDauer},
	//		       {"Bekantheit", Bekantheit},
	//		       {"Einheiten"};
	//
	// for (const auto& e : Einheiten)
	//{
	//	data["Einheiten"][e.getName()] = {
	//	    {"Hp", e.getLeben()},
	//	    {"Moral", e.getMoral()},
	//	    {"Starke", e.getStarke()},
	//	    {"Einsatzbereit", e.getEinsatzbereit()},
	//	    {"Xp", e.getErfahrung()},
	//	    {"Level", e.getLevel()},
	//	    {"Anzahl", e.getGrosse()}
	//
	//	};
	//}
	//
	// std::ofstream out("savegame.json");
	// out << std::setw(4) << data << std::endl;
}
