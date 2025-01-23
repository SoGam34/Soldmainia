#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>
#include <memory>
#include "../src/Data/Data.h"
#include "../src/Gebaude/Batilion_Ausbildungszentrum.h"
#include "../src/Rendern/Auswahl.h"

TEST_CASE("Testing the Timer Class") {
      std::shared_ptr<Data> data = std::make_shared<Data>();
      Auswahl a                  = Auswahl(data);

      data->addBattiliion(Battilion(10, 8, 12, 88, "Holgar"));
      data->addBattiliion(Battilion(11, 9, 13, 88, "asdf"));
      data->addBattiliion(Battilion(12, 10, 14, 88, "qwer"));
      data->addBattiliion(Battilion(13, 11, 16, 88, "wrtz"));
      data->addBattiliion(Battilion(14, 12, 15, 88, "dfgh"));
      data->addBattiliion(Battilion(15, 13, 11, 88, "wsdfg"));
      data->addBattiliion(Battilion(16, 14, 10, 88, "ztuikl"));

      a.sucheNachEinsetzbarenEinheiten();
      CHECK(a.getAusgewahlteEinheiten().size() == 7);

      SECTION("Starke sortieren") {
            a.sortiereNachStarke(true);
            auto e = a.getAusgewahlteEinheiten();
            CHECK(a.getAsEinheit(data->getMembers().at(e.at(0)))->getName() ==
                  "Holgar");
            CHECK(a.getAsEinheit(data->getMembers().at(e.at(1)))->getName() ==
                  "asdf");
            CHECK(a.getAsEinheit(data->getMembers().at(e.at(2)))->getName() ==
                  "qwer");
            CHECK(a.getAsEinheit(data->getMembers().at(e.at(3)))->getName() ==
                  "wrtz");
            CHECK(a.getAsEinheit(data->getMembers().at(e.at(4)))->getName() ==
                  "dfgh");
            CHECK(a.getAsEinheit(data->getMembers().at(e.at(5)))->getName() ==
                  "wsdfg");
            CHECK(a.getAsEinheit(data->getMembers().at(e.at(6)))->getName() ==
                  "ztuikl");

            a.sortiereNachStarke(false);

            CHECK(a.getAsEinheit(data->getMembers().at(e.at(0)))->getName() ==
                  "ztuikl");
            CHECK(a.getAsEinheit(data->getMembers().at(e.at(1)))->getName() ==
                  "wsdfg");
            CHECK(a.getAsEinheit(data->getMembers().at(e.at(2)))->getName() ==
                  "dfgh");
            CHECK(a.getAsEinheit(data->getMembers().at(e.at(3)))->getName() ==
                  "wrtz");
            CHECK(a.getAsEinheit(data->getMembers().at(e.at(4)))->getName() ==
                  "qwer");
            CHECK(a.getAsEinheit(data->getMembers().at(e.at(5)))->getName() ==
                  "asdf");
            CHECK(a.getAsEinheit(data->getMembers().at(e.at(6)))->getName() ==
                  "Holgar");
      }
}
