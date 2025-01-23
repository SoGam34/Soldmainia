#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include "../src/Timer.h"

TEST_CASE("Testing the Timer Class") {
      Timer t = Timer();

      REQUIRE(t.getTimerstand() == 0);
      REQUIRE(!t.getTimerstandMitID(0).has_value());

      REQUIRE(t.checkTimerAbgelaufen());

      auto time = GENERATE(4, 2, 44);

      t.neuerTimer(time);
      t.neuerTimerMitID(0, time);

      for (int i = 0; i < time; i++) {
            REQUIRE_FALSE(t.checkTimerAbgelaufen());
            REQUIRE(t.getTimerstand() == time - i);

            CHECK(t.getTimerstandMitID(0).value_or(0) > 0);
            REQUIRE_FALSE(t.checkTimerAbgelaufenMitID(0));

            t.aktTimer();
      }
      CHECK(t.checkTimerAbgelaufen());

      CHECKED_IF(t.getTimerstandMitID(0).has_value()) {
            INFO(t.getTimerstandMitID(0).value());
      }
      CHECKED_ELSE(t.getTimerstandMitID(0).has_value()) {
            WARN("Dont has a value");
      }

      t.aktTimer();

      CHECK(t.checkTimerAbgelaufen());

      CHECKED_IF(t.getTimerstandMitID(0).has_value()) {
            INFO(t.getTimerstandMitID(0).value());
      }
      CHECKED_ELSE(t.getTimerstandMitID(0).has_value()) {
            WARN("Dont has a value");
      }
      REQUIRE(t.checkTimerAbgelaufenMitID(0));
      REQUIRE_FALSE(t.checkTimerAbgelaufenMitID(1));
}
