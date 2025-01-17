#include "Data.h"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

Data::Data() {
      Members.clear();

      std::ifstream file("savegame.json");
      nlohmann::json data;
      file >> data;

      Kontostand = data["Kontostand"];
      AnzahlTage = data["AnzahlTage"];
      TagesDauer = data["TagesDauer"];
      Bekantheit = data["Bekantheit"];

      if (!data.contains("Einheiten")) {
            return;
      }
      for (const auto& Einheit : data["Einheiten"].items()) {
            std::string name = Einheit.key();

            if (Einheit.value().at("Type") == "Ek") {
                  Einzelkampfer e = Einzelkampfer(AbilityTyps::fire,
                                                  Einheit.value().at("Starke"),
                                                  Einheit.value().at("Starke"),
                                                  10,
                                                  name);
                  addEinzelkampfer(e);
            }

            if (Einheit.value().at("Type") == "Ba") {
                  Battilion e = Battilion(1,
                                          Einheit.value().at("Starke"),
                                          Einheit.value().at("Starke"),
                                          10,
                                          name);
                  addBattiliion(e);
            }
      }
}

std::vector<std::variant<Battilion, Einzelkampfer>>& Data::getMembers() {
      return Members;
}

void Data::addBattiliion(const Battilion& e) {
      Members.push_back(e);
}

void Data::addEinzelkampfer(const Einzelkampfer& e) {
      Members.emplace_back(e);
}

unsigned int Data::getBekanntheit() const {
      return Bekantheit;
}

void Data::setBekanntheit(unsigned int const value) {
      Bekantheit = value;
}

float Data::getKontostand() const {
      return Kontostand;
}

void Data::abziehnVonKontostand(float const betrag) {
      Kontostand -= betrag;
}

void Data::hinzufuegenZuKontostand(float const betrag) {
      Kontostand += betrag;
}

void Data::erhoheAnzahlTage() {
      AnzahlTage++;
}

int Data::getAnzahlTage() const {
      return AnzahlTage;
}

int Data::getMONATS_DAUER() const {
      return MONATS_DAUER;
}

double Data::getTagesDauer() const {
      return TagesDauer;
}

void Data::setTagesDauer(float const neueDauer) {
      TagesDauer = neueDauer;
}

void Data::saveGameToFile() {
      nlohmann::json data{
          {"Kontostand", Kontostand},
          {"AnzahlTage", AnzahlTage},
          {"TagesDauer", TagesDauer},
          {"Bekantheit", Bekantheit}
      };

      for (auto k : Members) {
            if (auto e = (std::get_if<Einzelkampfer>(&k))) {
                  data["Einheiten"][e->getName()] = {
                      {"Type",          "Ek"                              },
                      {"Hp",            e->getHealth()                    },
                      {"Moral",         e->getMental()                    },
                      {"Starke",        e->getTotalAmountOfDealingDamage()},
                      {"Einsatzbereit", e->getReady()                     },
                      {"Xp",            e->getExpierience()               },
                      {"Level",         e->getLevel()                     }
                  };
            }

            if (auto e = (std::get_if<Battilion>(&k))) {
                  data["Einheiten"][e->getName()] = {
                      {"Type",          "Ba"                              },
                      {"Hp",            e->getHealth()                    },
                      {"Moral",         e->getMental()                    },
                      {"Starke",        e->getTotalAmountOfDealingDamage()},
                      {"Einsatzbereit", e->getReady()                     },
                      {"Xp",            e->getExpierience()               },
                      {"Level",         e->getLevel()                     },
                      {"Anzahl",        e->getMemeberCount()              }
                  };
            };
      }

      std::ofstream out("savegame.json");
      out << std::setw(4) << data << std::endl;
}
