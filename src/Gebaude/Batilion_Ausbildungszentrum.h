#pragma once
#include "Gebaeude.h"

#include "../Data/Data.h"
#include "../Timer.h"

#include <memory>
#include <sstream>

class Batillion_Ausbildungszentrum : public Gebaeude {
     public:
      //--------------------------------Konstruktoren----------------------------------------------//
      Batillion_Ausbildungszentrum() = delete;

      // Konstrucktor mit allen informationen fuer eine vollstandige
      // Initzialisierung
      explicit Batillion_Ausbildungszentrum(std::shared_ptr<Data>& data);

      //--------------------------------Aufgaben
      // Ablauf----------------------------------------------//

      /*
       Name: GebaeudeAusfuhrungskosten
       param: keine
       Aufgabe: Die virtuelle Funktion berechnet wie viel die Ausfuhrung
       kostet Retrun: Die Funktion gibt die kosten als int zurueck Zu
       Beachten: Die Funktion ist in gebaude als virtuell deklarirt
       */
      unsigned int getGebaeudeAusfuhrungskosten() const override;

      /*
       Name: GebaudeAktivText
       param: keine
       Aufgabe: Die virtuelle Funktion erstellt den Text der Angezeigt wird
       wenn das Gebaude aktiv ist Retrun: Die Funktion gibt den Text als
       stringstram zurueck Zu Beachten: Die Funktion ist in gebaude als
       virtuell deklarirt
       */
      const std::stringstream getGebaudeAktivText() const override;

      /*
       Name: AnzahlErhohen
       param: keine
       Aufgabe: Die Funktion erhot die Groeße des Batillions was ausgebildet
       werden soll Retrun: keine
       */
      void erhoheEinheitsGrosse();

      /*
       Name: AnzahlReduzieren
       param: keine
       Aufgabe: Die Funktion rediziert die Groeße des Batillions was
       ausgebildet werden soll Retrun: keine
       */
      void reduziereEinheitsGrosse();

      /*
       Name: BeendenDerAusfuhrung
       param: keine
       Aufgabe: Die virtuelle Funktion sorgt fuer ein geregeltes Ende der
       Ausfuhrung Retrun: keine Zu Beachten: Die Funktion ist in gebaude als
       virtuell deklarirt
       */
      void beendenDerAusfuhrung();

      /*
       Name: Vorbereiten_neueAusbildung
       param: keine
       Aufgabe: Die Funktion bereitet alles fuer eine neue Ausbildung vor
       Retrun: keine
       */
      void vorbereiten_neueAusbildung();

      //--------------------------------Upgraden des
      // Gebaeudes----------------------------------------------//

      /*
       Name: ErhohenDerGrundstarke
       param: keine
       Aufgabe: Die Funktion modifiziert fGrundstaerke, sodass das Batillion
       starker ist und passt den Kontostand sowie die Kacheln an Retrun: keine
       */
      void erhohenDerGrundstarke();

     private:
      unsigned short int Batillionsgroesse = 10;
      float Grundstaerke                   = 10;
};
