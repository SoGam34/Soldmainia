#include "Auswahl.h"
#include <algorithm>
#include <memory>
#include <variant>

Auswahl::Auswahl(std::shared_ptr<Data> data) : DatenAuswahl(data) {
      AusgewahlteEinheiten.clear();
}

Einheit* Auswahl::getAsEinheit(
    std::variant<Battilion, Einzelkampfer>& t) const {
      if (auto* value = (std::get_if<Einzelkampfer>(&t))) {
            return value;
      }

      if (auto* value = (std::get_if<Battilion>(&t))) {
            return value;
      }

      return nullptr;
}

void Auswahl::sucheNachEinsetzbarenEinheiten() {
      for (size_t i = 0; i < DatenAuswahl->getMembers().size(); i++) {
            auto* e = getAsEinheit(DatenAuswahl->getMembers().at(i));

            if (e->getReady()) {
                  AusgewahlteEinheiten.emplace_back(i);
            }
      }

      entferneDopplungen();
}

void Auswahl::entferneDopplungen() {
      for (auto i = AusgewahlteEinheiten.begin();
           i != AusgewahlteEinheiten.end();
           i++) {
            for (auto j = AusgewahlteEinheiten.begin();
                 j != AusgewahlteEinheiten.end();
                 j++) {
                  if (*i == *j && i != j) {
                        AusgewahlteEinheiten.erase(j);
                  }
            }
      }
}

void Auswahl::sucheNachUnverletztenEinheiten() {
      for (size_t i = 0; i < DatenAuswahl->getMembers().size(); i++) {
            auto* e = getAsEinheit(DatenAuswahl->getMembers().at(i));

            if (e->getReady() && e->getHealth() == MAX_HEALTH_POINTS) {
                  AusgewahlteEinheiten.emplace_back(i);
            }
      }

      entferneDopplungen();
}

void Auswahl::sucheNachVerletzten() {
      for (size_t i = 0; i < DatenAuswahl->getMembers().size(); i++) {
            auto* e = getAsEinheit(DatenAuswahl->getMembers().at(i));
            if (e->getReady() && e->getHealth() < MAX_HEALTH_POINTS) {
                  AusgewahlteEinheiten.emplace_back(i);
            }
      }

      entferneDopplungen();
}

void Auswahl::sucheNachTruppenmoral() {
      for (size_t i = 0; i < DatenAuswahl->getMembers().size(); i++) {
            auto* e = getAsEinheit(DatenAuswahl->getMembers().at(i));
            if (e->getReady() && e->getMental() < MAX_MENTAL_POINTS) {
                  AusgewahlteEinheiten.emplace_back(i);
            }
      }

      entferneDopplungen();
}

void Auswahl::sucheNachStarke(int min) {
      for (size_t i = 0; i < DatenAuswahl->getMembers().size(); i++) {
            auto* e = getAsEinheit(DatenAuswahl->getMembers().at(i));
            if (e->getReady() && e->getTotalAmountOfDealingDamage() >= min) {
                  AusgewahlteEinheiten.emplace_back(i);
            }
      }

      entferneDopplungen();
}

void Auswahl::leeren() {
      for (; 0 < AusgewahlteEinheiten.size();) {
            AusgewahlteEinheiten.erase(AusgewahlteEinheiten.begin());
      }
}

void Auswahl::sortiereNachStarke(bool aufsteigend) {
      if (aufsteigend) {
            auto comp = [this](int i, int j) {
                  auto* I     = getAsEinheit(DatenAuswahl->getMembers().at(i));
                  auto* J     = getAsEinheit(DatenAuswahl->getMembers().at(j));

                  int starkeJ = J->getTotalAmountOfDealingDamage();
                  int starkeI = I->getTotalAmountOfDealingDamage();

                  return starkeI < starkeJ;
            };

            std::sort(AusgewahlteEinheiten.begin(),
                      AusgewahlteEinheiten.end(),
                      comp);

            return;
      }

      auto comp = [this](int i, int j) {
            auto* I     = getAsEinheit(DatenAuswahl->getMembers().at(i));
            auto* J     = getAsEinheit(DatenAuswahl->getMembers().at(j));

            int starkeJ = J->getTotalAmountOfDealingDamage();
            int starkeI = I->getTotalAmountOfDealingDamage();

            return starkeI > starkeJ;
      };

      std::sort(AusgewahlteEinheiten.rbegin(),
                AusgewahlteEinheiten.rend(),
                comp);
}

void Auswahl::sortiereNachVerletzten(bool aufsteigend) {
      if (aufsteigend) {
            auto comp = [this](int i, int j) {
                  auto* I     = getAsEinheit(DatenAuswahl->getMembers().at(i));
                  auto* J     = getAsEinheit(DatenAuswahl->getMembers().at(j));

                  int starkeJ = J->getHealth();
                  int starkeI = I->getHealth();

                  return starkeI < starkeJ;
            };

            std::sort(AusgewahlteEinheiten.begin(),
                      AusgewahlteEinheiten.end(),
                      comp);

            return;
      }

      auto comp = [this](int i, int j) {
            auto* I     = getAsEinheit(DatenAuswahl->getMembers().at(i));
            auto* J     = getAsEinheit(DatenAuswahl->getMembers().at(j));

            int starkeJ = J->getHealth();
            int starkeI = I->getHealth();

            return starkeI > starkeJ;
      };

      std::sort(AusgewahlteEinheiten.begin(), AusgewahlteEinheiten.end(), comp);
}

void Auswahl::sortiereNachTruppenmoral(bool aufsteigend) {
      if (aufsteigend) {
            auto comp = [this](int i, int j) {
                  auto* I     = getAsEinheit(DatenAuswahl->getMembers().at(i));
                  auto* J     = getAsEinheit(DatenAuswahl->getMembers().at(j));

                  int starkeJ = J->getMental();
                  int starkeI = I->getMental();

                  return starkeI < starkeJ;
            };

            std::sort(AusgewahlteEinheiten.begin(),
                      AusgewahlteEinheiten.end(),
                      comp);
            return;
      }

      auto comp = [this](int i, int j) {
            auto* I     = getAsEinheit(DatenAuswahl->getMembers().at(i));
            auto* J     = getAsEinheit(DatenAuswahl->getMembers().at(j));

            int starkeJ = J->getMental();
            int starkeI = I->getMental();

            return starkeI > starkeJ;
      };

      std::sort(AusgewahlteEinheiten.begin(), AusgewahlteEinheiten.end(), comp);
}
