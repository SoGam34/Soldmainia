#pragma once

/**
 * @file View.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-05-12
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "../../Data/Data.h"
#include "../../Menus.h"
#include "../Auswahl.h"
#include "../View.h"

#include <iostream>
#include <memory>
#include <utility>
#include <vector>

/**
 * @brief Die Klasse zeigt dem Spieler alles an und leitet die eingabe an Game
 * weiter.
 *
 */
class Gui : public View {
     public:
      // De/Konstrucktor
      Gui() = delete;

      /**
       * @brief Construct a new View object
       *
       * @param data Eine Kopie des Data Pointers.
       */
      Gui(std::shared_ptr<Data> data);

      /**
       * @brief Die Funktion gibt an ob der Spieler das Spiel beendet hat oder
       * nicht.
       *
       * @return true Das Spieler will weiter Spielen.
       * @return false Der Spieler will das Spiel beenden.
       */
      bool getSpielIstAktiv() const override;

      /**
       * @brief Get the Eingabe object
       *
       * @return int Die eingabe des Spielers

       * @attention Die Funktion gibt die Eingabe vom Spieler dierekt wieder
       **ohne** auf irgendwas zu prüfen. Das selbständige Prüfen ist daher
       essentiel.
       * @link ungueltigeEingabe() @endlink
       */
      int getLetzteNutzerEingabe() const override;

      /**
       * @brief Die Funktion rendert das Spiel.
       *
       * @param aktuellesMenu Das Menu in dem Sich der Spieler grade befindet.
       * @param stats Die Upgrade informationen des Gebaudes in dem der
       * Spieler sich gerade befindet.
       */
      void ausgabe(Menus aktuellesMenu,
                   GebaeudeUpgradeStats stats,
                   InProgressStats progress) override;

      /**
       * @brief Ein Interaktives Sondermenu bei dem der Spieler eine Einheit
       für den Aufrufer aussucht.
       *
       * @param verwendugszweck Für was wird die Einheit ausgewählt.

       * @return int Der Index der Einheit. Mögliche Verwendung
       * 	 @code {.cpp}
       *   Data::getEinheiten()[View::dialogAuswahlEinheit("Auswahl für ...")]
       *   @endcode
       *   gibt die vom Spieler gewählte Einheit zurück.
       */
      int dialogAuswahlEinheit(std::string const& verwendungszweck) override;

      /**
       * @brief Die Eingabe ist nicht richtig und kann keiner Aktion
       * zugeordnet werden.
       *
       */
      void ungueltigeEingabe() override;

      /**
       * @brief Starten einer neuen Benarichtigung. Lauft bereits eine
       * Benarichtigung werden beide Gleichzeitig angezeigt.
       * @warning Die Funktion ist noch nicht implementiert.
       *
       * @param benarichtigungsText Der Text der Angezeigt werden soll.
       * @param benarichtigungsArt Die Art der Benarichtigung.
       * @param gutfuerSpieler Bringt das Ereigniss den Spieler voran oder
       * nicht, z. B. ist der Auftrag erfolgreich Abgeschlossen oder
       * gescheitert.
       */
      void addBenarichtigung(std::string const& benarichtigungsText,
                             int benarichtigungsArt,
                             bool gutfuerSpieler) override;
};