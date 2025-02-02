#include <catch2/catch_test_macros.hpp>
#include <memory>
#include <stdexcept>
#include "../src/Data/Data.h"

TEST_CASE("Testing Data") {
      std::shared_ptr<Data> daten = std::make_shared<Data>();

      REQUIRE(daten->getAnzahlTage() == 0);
      REQUIRE(daten->getTagesDauer() == 1.2);
      REQUIRE(daten->getMONATS_DAUER() == 30);
      REQUIRE(daten->getBekanntheit() == 0);
      REQUIRE(daten->getKontostand() == 10000);
      REQUIRE(daten->getMembers().size() == 0);

      SECTION("Kontostand") {
            REQUIRE(daten->getKontostand() == 10000);
            REQUIRE_NOTHROW(daten->abziehnVonKontostand(100));
            REQUIRE(daten->getKontostand() == 9900);
            REQUIRE_THROWS_AS(daten->abziehnVonKontostand(-100),
                              std::invalid_argument);
            REQUIRE_NOTHROW(daten->abziehnVonKontostand(100));
            REQUIRE(daten->getKontostand() == 9800);
            daten->abziehnVonKontostand(10000000);
            REQUIRE(daten->getKontostand() == -9990200);
            REQUIRE_THROWS(daten->abziehnVonKontostand(-10000000));
            REQUIRE(daten->getKontostand() == -9990200);
      }
      SECTION("Speichern") {
            REQUIRE_NOTHROW(daten->saveGameToFile());
      }
}
