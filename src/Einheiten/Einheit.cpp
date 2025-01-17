#include "Einheit.h"
#include "Einheiten_CONST.h"
Einheit::Einheit(int const BasisDealingDamage,
                 int const BasisProtaction,
                 int const minExpierienceForLevelUpgrade,
                 std::string const& name)
    : BasisDealingDamage(BasisDealingDamage),
      BasisProtaction(BasisProtaction),
      minExpierienceForLevelUpgrade(minExpierienceForLevelUpgrade),
      Name(name) {}

Waffen& Einheit::getPrimaryWeapon() {
      return PrimaryWeapon;
}
Waffen& Einheit::getSecondaryWeapon() {
      return SecondaryWeapon;
}
Rüstung& Einheit::getArmor() {
      return Armor;
}
std::string& Einheit::getName() {
      return Name;
}
int Einheit::getHealth() const {
      return HealtPoints;
}

bool Einheit::getReady() const

{
      return Einsatzbereit;
}
int Einheit::getMental() const {
      return MentalPoints;
}
int Einheit::getLevel() const {
      return Level;
}
int Einheit::getminExpierienceForLevelUpgrade() const {
      return minExpierienceForLevelUpgrade;
}
int Einheit::getExpierience() const {
      return Expierience;
}
int Einheit::getTotalAmountOfDealingDamage() const {
      // FIXME(Einheit): Richtiges Berechnen des Schadens
      return BasisDealingDamage;
}
int Einheit::getTotalAmountOfProtaction() const {
      // FIXME(Einheit): Richtiges BErechnen des Schutzes
      return BasisProtaction;
}

void Einheit::addExpierience(int const additionalExpierience) {
      Expierience += additionalExpierience;
      while (Expierience > minExpierienceForLevelUpgrade) {
            Level++;
            Expierience                   -= minExpierienceForLevelUpgrade;
            minExpierienceForLevelUpgrade += Level * 10;
      }
}

void Einheit::addDamage(int const Damage) {
      HealtPoints -= Damage;
      if (HealtPoints < 0) {
            HealtPoints = 0;
      }
}
void Einheit::recoverHealth(int const newHealthPoints) {
      HealtPoints += newHealthPoints;
      if (HealtPoints > MAX_HEALTH_POINTS * Level) {
            HealtPoints = MAX_HEALTH_POINTS * Level;
      }
}
void Einheit::recoverMental(int const newMentalPoints) {
      MentalPoints += newMentalPoints;
      if (MentalPoints > MAX_MENTAL_POINTS * Level) {
            MentalPoints = MAX_MENTAL_POINTS * Level;
      }
}
void Einheit::reduceMentalPonitsBy(int const amountToReduce) {
      MentalPoints -= amountToReduce;
      if (MentalPoints < 0) {
            MentalPoints = 0;
      }
}

void Einheit::equipArmor(Rüstung const& ArmorToEquip) {
      Armor = ArmorToEquip;
}

void Einheit::equipPrimaryWeapon(Waffen const& WeaponToEquip) {
      PrimaryWeapon = WeaponToEquip;
}
void Einheit::equipSecondaryWeapon(Waffen const& WeaponToEquip) {
      SecondaryWeapon = WeaponToEquip;
}
