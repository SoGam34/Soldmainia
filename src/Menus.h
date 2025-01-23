#pragma once
#include <string>
/**
 * @file Timer.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-05-10
 *
 * @copyright Copyright (c) 2024
 *
 */

/**
 * @brief Speichert in welchem Menu sich der Spieler gerade befindet
 *
 */
enum Menus {
      hauptmenu                  = 1,
      zentrale                   = 2,
      scoutbuero                 = 3,
      batillionsausbildungsstate = 4,
      traningszentrum            = 5,
      auftraege                  = 6,
      aauftraege                 = 7,
      logistikSystem             = 8,
      erholungsresort            = 9,
      einzelMitglieder           = 11,
      batillione                 = 12
};

struct InProgressStats {
      std::string ProgressText;
      bool hasProgress{false};
};

/**
 * @brief Speichert die Aktuellen Upgrade Werte einer Einrichtung
 *
 */
struct GebaeudeUpgradeStats {
      /**
       * @brief Speichert wie viel das Zeit Upgrade Kostet
       *
       */
      float BeschlaunigunsKosten{1};
      /**
       * @brief Speichert welchen Effekt das Upgrade hat in Prozent
       *
       */
      float BeschlaunigungsFaktor{0};

      bool BeschlaunigungsUpgradeMaxLevel{false};

      /**
       * @brief Speichert wie viel das Zeit Upgrade Kostet
       *
       */
      float GebaudeSpezielleKosten{1};
      /**
       * @brief Speichert welchen Effekt das Upgrade hat in Prozent
       *
       */
      float GebaudeSpezielleFaktor{0};

      bool GebaudeSpezielleUpgradeMaxLevel{false};

      /**
       * @brief Speichert wie viel das Zeit Upgrade Kostet
       *
       */
      float AusführungsReduzierungsKosten{1};
      /**
       * @brief Speichert welchen Effekt das Upgrade hat in Prozent
       *
       */
      float AusführungsReduzierungsFaktor{0};

      bool AusführungsReduzierungsUpgradeMaxLevel{false};
};

constexpr int AUSWAHL_MENU_ZENTRALE                   = 1;
constexpr int AUSWAHL_MENU_BATILIONAUSBILDUNGSZENTRUM = 2;
constexpr int AUSWAHL_MENU_SCOUTBUERO                 = 3;
constexpr int AUSWAHL_MENU_ERHOLUNGSRESORT            = 4;
constexpr int AUSWAHL_MENU_TRANINGSZENTRUM            = 5;
constexpr int AUSWAHL_MENU_VERFUEGBARE_AUFTRAGE       = 6;
constexpr int AUSWAHL_MENU_LAUFENDE_AUFTRAGE          = 7;
constexpr int AUSWAHL_MENU_LOGISTIK_SYSTEM            = 8;
constexpr int AUSWAHL_MENU_HAUPTMENU                  = 9;

constexpr int AUSWAHL_AKTION_1                        = 10;
constexpr int AUSWAHL_AKTION_2                        = 11;
constexpr int AUSWAHL_AKTION_3                        = 12;

constexpr int AUSWAHL_UPGRADE_ZEIT                    = 13;
constexpr int AUSWAHL_UPGRADE_SPEZIFISCH              = 14;
constexpr int AUSWAHL_UPGRADE_KOSTEN                  = 15;

constexpr int AUSWAHL_SPEICHERN                       = 16;
constexpr int AUSWAHL_BEENDEN                         = 17;
constexpr int AUSWAHL_HILFE                           = 18;
