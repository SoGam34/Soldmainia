#include "PreHeader.h"
#include "Auswahl.h"

Auswahl::Auswahl()
{
	myData = nullptr;
}

Auswahl::~Auswahl()
{

}

void Auswahl::AnzeigeVorbereitung()
{
}

void Auswahl::SucheNachEinsetzbarenEinheiten()
{
}

void Auswahl::SucheNachVerletzten()
{
}

void Auswahl::SucheNachTruppenmoral()
{
}

void Auswahl::SucheNachStarke()
{
}

void Auswahl::SucheNachKampfkraft()
{
}

void Auswahl::up()
{
	std::sort(vAusgewahlten.begin(), vAusgewahlten.end(),
		[](const auto& x, const auto& y) { return x.second < y.second; });
}

void Auswahl::down()
{
	std::sort(vAusgewahlten.begin(), vAusgewahlten.end(),
		[](const auto& x, const auto& y) { return x.second > y.second; });
}

std::string Auswahl::getEinheitsname(int ButtenID)
{
	return vAusgewahlten[ButtenID].first;
}

void Auswahl::Testhin(std::string Text, int ID)
{
	vAusgewahlten.push_back(std::make_pair(Text, ID));
}

void Auswahl::print()
{
	for (auto e : vAusgewahlten)
		std::cout << e.first << ":" << e.second << "\n";
}

void Auswahl::setData(Data* data)
{
	myData = data;
}
