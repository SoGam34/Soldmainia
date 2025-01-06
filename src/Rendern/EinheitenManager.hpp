#pragma once
#include "../Einheiten/Battelion.h"
#include "../Einheiten/Einheit.h"
#include "../Einheiten/Einzelkampfer.h"

#include <optional>
class EinheitenManager
{
	/*Einheit getEinheit()
	{
	      if (e.first.has_value()) {
	      return e.first.value();
	      }
	      return dynamic_cast<Einheit>(e.second.value());
	}
  */

	std::pair<std::optional<Battilion>, std::optional<Einzelkampfer>> e;
};