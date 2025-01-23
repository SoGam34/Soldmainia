#include "tui.h"
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_DEBUG
#include <spdlog/spdlog.h>

Tui::Tui(std::shared_ptr<Data> data) : View(data) {}

bool Tui::getSpielIstAktiv() const {
      SPDLOG_LOGGER_ERROR(log, "Tui::getSpielIstAktiv is not implementet!");
}

int Tui::getLetzteNutzerEingabe() const {
      SPDLOG_LOGGER_ERROR(log,
                          "Tui::getLetzteNutzerEingabe is not implementet!");
}

void Tui::ausgabe(Menus aktuellesMenu,
                  GebaeudeUpgradeStats stats,
                  InProgressStats progress) {
      SPDLOG_LOGGER_ERROR(log, "Tui::ausgabe is not implementet!");
}

int Tui::dialogAuswahlEinheit(std::string const& verwendungszweck) {
      SPDLOG_LOGGER_ERROR(log, "Tui::dialogAuswahlEinheit is not implementet!");
}

void Tui::ungueltigeEingabe() {
      SPDLOG_LOGGER_ERROR(log, "Tui::ungueltigeEingabe is not implementet!");
}

void Tui::addBenarichtigung(std::string const& benarichtigungsText,
                            int benarichtigungsArt,
                            bool gutfuerSpieler) {
      SPDLOG_LOGGER_ERROR(log, "Tui::addBenarichtigung is not implementet!");
}