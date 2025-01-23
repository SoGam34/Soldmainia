#include "Game.h"
#include <spdlog/common.h>
#include <spdlog/formatter.h>
#include <iostream>
#include <memory>
#include <sstream>
#include <variant>
#include "Einheiten/Battelion.h"
#include "Menus.h"
#include "Rendern/View.h"
#include "spdlog/sinks/basic_file_sink.h"

Game::Game(View* v, std::shared_ptr<Data> daten)
    : AktuellesMenu(hauptmenu),
      Daten(daten) {
      // Gebaude
      BAZ              = std::make_unique<Batillion_Ausbildungszentrum>(Daten);
      Scoutbueros      = std::make_unique<Scoutbuero>(Daten);
      Traningzentren   = std::make_unique<Traningszentrum>(Daten);
      Hauptquatier     = std::make_unique<Zentrale>(Daten);
      Erholungsresorts = std::make_unique<Erholungsresort>(Daten);

      view.reset(v);

      ZeitpunktDesLetztenTages = std::chrono::steady_clock::now();

      Stats                    = GebaeudeUpgradeStats();
      Progress                 = InProgressStats();

      try {
            log = spdlog::basic_logger_mt("GameLogger",
                                          "progam-logs/game-log.txt");
      } catch (const spdlog::spdlog_ex& ex) {
            std::cout << "Log init failed: " << ex.what() << std::endl;
            return;
      }
}

void Game::spielLauft() {
      while (view->getSpielIstAktiv()) {
            update();

            zeit();

            view->ausgabe(AktuellesMenu, Stats, Progress);
      }

      log->flush();

      Daten->saveGameToFile();
}

void Game::processBattilion(int const eingabe) {
      switch (eingabe) {
            case AUSWAHL_AKTION_1: {
                  BAZ->beginneAufgabe();

                  std::stringstream temp;
                  temp << "Kosten: " << BAZ->getGebaeudeAusfuhrungskosten();
                  view->addBenarichtigung(temp.str(), 0, false);
            } break;
            case AUSWAHL_AKTION_2: {
                  BAZ->erhoheEinheitsGrosse();
            } break;
            case AUSWAHL_AKTION_3: {
                  BAZ->reduziereEinheitsGrosse();
            } break;
            case AUSWAHL_UPGRADE_ZEIT: {
                  // TODO(Kosten): Benarichtigung
                  BAZ->beschleunigungDerAufgabenDurchfuehrung();
            } break;
            case AUSWAHL_UPGRADE_SPEZIFISCH: {
                  // TODO(Kosten): Benarichtigung
                  BAZ->erhohenDerGrundstarke();
            } break;
            case AUSWAHL_UPGRADE_KOSTEN: {
                  // TODO(Kosten): Benarichtigung
                  BAZ->reduzierenDerAusfuhrungsKosten();
            } break;
            default: {
                  view->ungueltigeEingabe();
            } break;
      }

      Stats    = BAZ->getUpgradeStats();
      Progress = BAZ->getProgressStats();
}

void Game::processScoutbuero(int const eingabe) {
      switch (eingabe) {
            case AUSWAHL_AKTION_1: {
                  Scoutbueros->beginneAufgabe();  // Suche Starten
            } break;
            case AUSWAHL_UPGRADE_ZEIT: {
                  // TODO(Kosten): Benarichtigung
                  Scoutbueros->beschleunigungDerAufgabenDurchfuehrung();
            } break;
            case AUSWAHL_UPGRADE_SPEZIFISCH: {
                  // TODO(Kosten): Benarichtigung
                  Scoutbueros->erhohenDesMoeglichenRanges();
            } break;
            case AUSWAHL_UPGRADE_KOSTEN: {
                  // TODO(Kosten): Benarichtigung
                  Scoutbueros->reduzierenDerAusfuhrungsKosten();
            } break;
            case 25: {
                  // TODO(Einheit): Benarichtigung
                  Scoutbueros->annehmenDerEinheit();  // Annehmen
            } break;
            case 26: {
                  // TODO(Einheit): Benarichtigung
                  Scoutbueros->ablehnenDerEinheit();  // Ablehnen
            } break;
            default: {
                  view->ungueltigeEingabe();
            } break;
      }

      Stats    = Scoutbueros->getUpgradeStats();
      Progress = Scoutbueros->getProgressStats();
}

void Game::processTraningszentrum(int const eingabe) {
      switch (eingabe) {
            case AUSWAHL_UPGRADE_ZEIT: {
                  // TODO(Kosten): Benarichtigung
                  Traningzentren->beschleunigungDerAufgabenDurchfuehrung();
            } break;
            case AUSWAHL_UPGRADE_SPEZIFISCH: {
                  // TODO(Kosten): Benarichtigung
                  Traningzentren->erhohenDerTraningsWirksamkeit();
            } break;
            case AUSWAHL_UPGRADE_KOSTEN: {
                  // TODO(Kosten): Benarichtigung
                  Traningzentren->reduzierenDerAusfuhrungsKosten();
            } break;
            case AUSWAHL_AKTION_1: {
                  Traningzentren->langeTrainingsDauer();
                  int ausgewaelteEinheit{
                      view->dialogAuswahlEinheit("ein langes Traning")};
                  Traningzentren->auswahlZuOrdnen(ausgewaelteEinheit);
            } break;
            case AUSWAHL_AKTION_3: {
                  Traningzentren->kurzeTraningsDauer();
                  int ausgewaelteEinheit =
                      view->dialogAuswahlEinheit("ein kurzes Traning");
                  Traningzentren->auswahlZuOrdnen(ausgewaelteEinheit);
            } break;
            case AUSWAHL_AKTION_2: {
                  Traningzentren->mittlereTrainingsDauer();
                  int ausgewaelteEinheit =
                      view->dialogAuswahlEinheit("ein mittellanges Traning");
                  Traningzentren->auswahlZuOrdnen(ausgewaelteEinheit);
            } break;
            default: {
                  view->ungueltigeEingabe();
            } break;
      }

      Stats    = Traningzentren->getUpgradeStats();
      Progress = Traningzentren->getProgressStats();
}

void Game::processErholungsresort(int const eingabe) {
      switch (eingabe) {
            case AUSWAHL_AKTION_1: {
                  int ausgewaelteEinheit =
                      view->dialogAuswahlEinheit("eine Erholung");
                  Erholungsresorts->auswahlZuOrdnen(ausgewaelteEinheit);
            } break;
            case AUSWAHL_UPGRADE_ZEIT: {
                  // TODO(Kosten): Benarichtigung
                  Erholungsresorts->beschleunigungDerAufgabenDurchfuehrung();
            } break;
            case AUSWAHL_UPGRADE_SPEZIFISCH: {
                  // TODO(Kosten): Benarichtigung
                  Erholungsresorts->erhohenDerTraningsWirksamkeit();
            } break;
            case AUSWAHL_UPGRADE_KOSTEN: {
                  // TODO(Kosten): Benarichtigung
                  Erholungsresorts->reduzierenDerAusfuhrungsKosten();
            } break;
            default: {
                  view->ungueltigeEingabe();
            } break;
      }

      Stats    = Erholungsresorts->getUpgradeStats();
      Progress = Erholungsresorts->getProgressStats();
}

bool Game::changedMenu(int const eingabe) {
      switch (eingabe) {
            case AUSWAHL_MENU_ZENTRALE: {
                  AktuellesMenu = zentrale;
                  return true;
            } break;
            case AUSWAHL_MENU_BATILIONAUSBILDUNGSZENTRUM: {
                  AktuellesMenu = batillionsausbildungsstate;
                  return true;
            } break;
            case AUSWAHL_MENU_TRANINGSZENTRUM: {
                  AktuellesMenu = traningszentrum;
                  return true;
            } break;
            case AUSWAHL_MENU_SCOUTBUERO: {
                  AktuellesMenu = scoutbuero;
                  return true;
            } break;
            case AUSWAHL_MENU_ERHOLUNGSRESORT: {
                  AktuellesMenu = erholungsresort;
                  return true;
            } break;
            case AUSWAHL_MENU_VERFUEGBARE_AUFTRAGE: {
                  AktuellesMenu = auftraege;
                  return true;
            } break;
            case AUSWAHL_MENU_LAUFENDE_AUFTRAGE: {
                  AktuellesMenu = aauftraege;
                  return true;
            } break;
            case AUSWAHL_MENU_LOGISTIK_SYSTEM: {
                  AktuellesMenu = logistikSystem;
                  return true;
            } break;
      }
      return false;
}

void Game::update() {
      int const eingabe = view->getLetzteNutzerEingabe();

      if (eingabe == AUSWAHL_SPEICHERN) {
            Daten->saveGameToFile();
            return;
      }

      if (changedMenu(eingabe)) {
            return;
      }

      switch (AktuellesMenu) {
            case zentrale: {
                  AktuellesMenu = hauptmenu;
                  return;
            } break;

            case batillionsausbildungsstate: {
                  processBattilion(eingabe);
            } break;

            case scoutbuero: {
                  processScoutbuero(eingabe);
            } break;

            case traningszentrum: {
                  processTraningszentrum(eingabe);
            } break;

            case erholungsresort: {
                  processErholungsresort(eingabe);
            } break;
      }
}

void Game::zeit() {
      std::chrono::time_point<std::chrono::steady_clock> aktuellerZeitpunkt =
          std::chrono::steady_clock::now();

      std::chrono::duration<double> vergangeneZeit =
          aktuellerZeitpunkt - ZeitpunktDesLetztenTages;

      int daycount =
          static_cast<double>(vergangeneZeit.count()) / Daten->getTagesDauer();

      while (daycount-- > 0) {
            Daten->erhoheAnzahlTage();

            BAZ->aktualisierenTimer();
            Scoutbueros->aktualisierenTimer();
            Traningzentren->aktualisierenTimer();
            Erholungsresorts->aktualisierenTimer();

            if (Daten->getAnzahlTage() % Daten->getMONATS_DAUER() == 0) {
                  float totalSold = 0;
                  for (auto e : Daten->getMembers()) {
                        if (auto value = std::shared_ptr<Battilion>(
                                std::get_if<Battilion>(&e))) {
                              totalSold += value->getSold();
                        }
                  }
                  Daten->abziehnVonKontostand(totalSold);

                  std::stringstream temp;
                  temp << "Sold wird ausgezahlt! Insgesamt werden "
                          "deswegen "
                       << totalSold << " abgezogen.";
                  view->addBenarichtigung(temp.str(), 0, false);
            }

            ZeitpunktDesLetztenTages = std::chrono::steady_clock::now();
      }
}
