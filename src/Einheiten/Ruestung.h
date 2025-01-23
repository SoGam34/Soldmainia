#ifndef Ruestung_H_
#define Ruestung_H_

#include <string>
#include "Einheiten_CONST.h"
#include "Gegenstand.h"
class Ruestung : public Gegenstand {
      int Protaction;

     public:
      int getProtaction() const;

      std::string getDiscriptionText() override;
};

#endif
