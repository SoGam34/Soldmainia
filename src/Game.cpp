#include "Game.h"
#include "Einheiten/Battelion.h"

#include "Menus.h"

#include "Rendern/ViewIn.h"

#include "spdlog/sinks/basic_file_sink.h"

#include <iostream>

#include <memory>

#include <spdlog/common.h>

#include <spdlog/formatter.h>

#include <sstream>

#include <variant>

Game::Game(ViewIn* v, std::shared_ptr<Data> daten)
    : AktuellesMenu(hauptmenu),
      Daten(daten) {
      // Gebaude
      BAZ              = new Batillion_Ausbildungszentrum(Daten);

      Scoutbueros      = new Scoutbuero(Daten);

      Traningzentren   = new Traningszentrum(Daten);

      Hauptquatier     = new Zentrale(Daten);

      Erholungsresorts = new Erholungsresort(Daten);

      view.reset(v);

      ZeitpunktDesLetztenTages = std::chrono::steady_clock::now();

      Stats                    = GebaeudeUpgradeStats();
      Progress                 = InProgressStats();

      try {
            log =
                spdlog::basic_logger_mt("basic_logger", "progam/basic-log.txt");
      } catch (const spdlog::spdlog_ex& ex) {
            std::cout << "Log init failed: " << ex.what() << std::endl;
            return;
      }
}

Game::~Game() {
      delete BAZ;
      delete Scoutbueros;
      delete Traningzentren;
      delete Hauptquatier;
      delete Erholungsresorts;
}

void Game::spielLauft() {
      // Daten->addBattiliion(Battilion(1, 1, 1, 1, "Gunter"));
      // Daten->addBattiliion(Battilion(1, 3, 1, 1, "justin"));
      // Daten->addBattiliion(Battilion(1, 2, 1, 1, "halo"));
      view->dialogAuswahlEinheit("Test");
      Daten->saveGameToFile();
      return;

      while (view->getSpielIstAktiv()) {
            // log->info("starting new GameLoop");

            update();

            zeit();

            view->ausgabe(AktuellesMenu, Stats, Progress);
      }

      log->flush();

      Daten->saveGameToFile();
}

void Game::update() {
      int const eingabe = view->getLetzteNutzerEingabe();

      if (eingabe == AUSWAHL_SPEICHERN) {
            Daten->saveGameToFile();
            return;
      }

      switch (AktuellesMenu) {
            case zentrale: {
                  AktuellesMenu = hauptmenu;
                  return;
            } break;

            case batillionsausbildungsstate: {
                  switch (eingabe) {
                        case AUSWAHL_AKTION_1: {
                              BAZ->beginneAufgabe();

                              std::stringstream temp;
                              temp << "Kosten: "
                                   << BAZ->getGebaeudeAusfuhrungskosten();
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
            } break;

            case scoutbuero: {
                  switch (eingabe) {
                        case AUSWAHL_AKTION_1: {
                              Scoutbueros->beginneAufgabe();  // Suche Starten
                        } break;
                        case AUSWAHL_UPGRADE_ZEIT: {
                              // TODO(Kosten): Benarichtigung
                              Scoutbueros
                                  ->beschleunigungDerAufgabenDurchfuehrung();
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
            } break;

            case traningszentrum: {
                  switch (eingabe) {
                        case AUSWAHL_UPGRADE_ZEIT: {
                              // TODO(Kosten): Benarichtigung
                              Traningzentren
                                  ->beschleunigungDerAufgabenDurchfuehrung();
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
                              int ausgewaelteEinheit{view->dialogAuswahlEinheit(
                                  "ein langes Traning")};
                              Traningzentren->auswahlZuOrdnen(
                                  ausgewaelteEinheit);
                        } break;
                        case AUSWAHL_AKTION_3: {
                              Traningzentren->kurzeTraningsDauer();
                              int ausgewaelteEinheit =
                                  view->dialogAuswahlEinheit(
                                      "ein kurzes Traning");
                              Traningzentren->auswahlZuOrdnen(
                                  ausgewaelteEinheit);
                        } break;
                        case AUSWAHL_AKTION_2: {
                              Traningzentren->mittlereTrainingsDauer();
                              int ausgewaelteEinheit =
                                  view->dialogAuswahlEinheit(
                                      "ein mittellanges Traning");
                              Traningzentren->auswahlZuOrdnen(
                                  ausgewaelteEinheit);
                        } break;
                        default: {
                              view->ungueltigeEingabe();
                        } break;
                  }

                  Stats    = Traningzentren->getUpgradeStats();
                  Progress = Traningzentren->getProgressStats();
            } break;

            case erholungsresort: {
                  switch (eingabe) {
                        case AUSWAHL_AKTION_1: {
                              int ausgewaelteEinheit =
                                  view->dialogAuswahlEinheit("eine Erholung");
                              Erholungsresorts->auswahlZuOrdnen(
                                  ausgewaelteEinheit);
                        } break;
                        case AUSWAHL_UPGRADE_ZEIT: {
                              // TODO(Kosten): Benarichtigung
                              Erholungsresorts
                                  ->beschleunigungDerAufgabenDurchfuehrung();
                        } break;
                        case AUSWAHL_UPGRADE_SPEZIFISCH: {
                              // TODO(Kosten): Benarichtigung
                              Erholungsresorts->erhohenDerTraningsWirksamkeit();
                        } break;
                        case AUSWAHL_UPGRADE_KOSTEN: {
                              // TODO(Kosten): Benarichtigung
                              Erholungsresorts
                                  ->reduzierenDerAusfuhrungsKosten();
                        } break;
                        default: {
                              view->ungueltigeEingabe();
                        } break;
                  }

                  Stats    = Erholungsresorts->getUpgradeStats();
                  Progress = Erholungsresorts->getProgressStats();
            } break;
      }

      // Das Switch Statement ist zum einen das Hauptmenu zum andern
      // ermöglicht es 'Shortcuts' sodass man immer die Zahl für
      // AUSWAHL_MENU_ZENTRALE eingeben kann und im nächsten frame sich in der
      // Zentrale befindet.
      switch (eingabe) {
            case AUSWAHL_MENU_ZENTRALE: {
                  AktuellesMenu = zentrale;
            } break;
            case AUSWAHL_MENU_BATILIONAUSBILDUNGSZENTRUM: {
                  AktuellesMenu = batillionsausbildungsstate;
            } break;
            case AUSWAHL_MENU_TRANINGSZENTRUM: {
                  AktuellesMenu = traningszentrum;
            } break;
            case AUSWAHL_MENU_SCOUTBUERO: {
                  AktuellesMenu = scoutbuero;
            } break;
            case AUSWAHL_MENU_ERHOLUNGSRESORT: {
                  AktuellesMenu = erholungsresort;
            } break;
            case AUSWAHL_MENU_VERFUEGBARE_AUFTRAGE: {
                  AktuellesMenu = auftraege;
            } break;
            case AUSWAHL_MENU_LAUFENDE_AUFTRAGE: {
                  AktuellesMenu = aauftraege;
            } break;
            case AUSWAHL_MENU_LOGISTIK_SYSTEM: {
                  AktuellesMenu = logistikSystem;
            } break;
                  // default:
                  //{
                  //	AktuellesMenu = hauptmenu;
                  // }
                  // break;
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
