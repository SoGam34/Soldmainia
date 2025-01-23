#include "gui.h"
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_DEBUG
#include <spdlog/spdlog.h>
Gui::Gui(std::shared_ptr<Data> data) : View(data) {}

bool Gui::getSpielIstAktiv() const {
      SPDLOG_LOGGER_ERROR(log, "Gui::getSpielIstAktiv is not implementet!");
}

int Gui::getLetzteNutzerEingabe() const {
      SPDLOG_LOGGER_ERROR(log,
                          "Gui::getLetzteNutzerEingabe is not implementet!");
}

void Gui::ausgabe(Menus aktuellesMenu,
                  GebaeudeUpgradeStats stats,
                  InProgressStats progress) {
      SPDLOG_LOGGER_ERROR(log, "Gui::ausgabe is not implementet!");
}

int Gui::dialogAuswahlEinheit(std::string const& verwendungszweck) {
      SPDLOG_LOGGER_ERROR(log, "Gui::dialogAuswahlEinheit is not implementet!");
}

void Gui::ungueltigeEingabe() {
      SPDLOG_LOGGER_ERROR(log, "Gui::ungueltigeEingabe is not implementet!");
}

void Gui::addBenarichtigung(std::string const& benarichtigungsText,
                            int benarichtigungsArt,
                            bool gutfuerSpieler) {
      SPDLOG_LOGGER_ERROR(log, "Gui::addBenarichtigung is not implementet!");
}