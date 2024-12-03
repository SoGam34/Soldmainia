/**
 * @file Einheit.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-05-12
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef EINHEIT_H_
#define EINHEIT_H_

#include <string>

/**
 * @brief Eine Baseis Klasse für die Batilione und Einzelkämpfer.
 *
 */
class Einheit
{

	/**
	 * @brief Gibt an wie viel Leben eine Einheit hat.
	 *
	 */
	unsigned short int HP;

	/**
	 * @brief Gibt an wie die Truppenmoral ist gut gelaunt oder ehr weniger.
	 *
	 */
	unsigned short int Moral;

	/**
	 * @brief Wie Stark bzw. wie viel Kraft eine Einheit hat.
	 *
	 */
	unsigned short int Starke;

	/**
	 * @brief Ob die Einheit bereits Beschäftigt ist. True, die Einheit ist
	 * Beschäftigt. False, die Einheit ist frei.
	 *
	 */
	bool Einsatzbereit;

	/**
	 * @brief Der Name der Einheit.
	 *
	 */
	std::string Name;

	/**
	 * @brief Wie viel Erfahrung die Einheit im aktuellen Level hat.
	 *
	 */
	unsigned int XP;

	/**
	 * @brief Auf welchem Level die Einheit ist, je hoher das Level desto
	 * starker die Einheit.
	 *
	 */
	unsigned int Level;

	/**
	 * @brief Mit welcher Waffe die Einheit Hauptsächlich ausgerustet ist.
	 *
	 */
	int Hauptwaffe;

	/**
	 * @brief Eine Nebenwaffe die gelegentlich Benutzt wird.
	 *
	 */
	int Nebenwaffe;

	/**
	 * @brief Was für eine Rüstung die Einheit hat.
	 *
	 */
	int Rüstung;

	public:
	Einheit() = delete;

	/**
	 * @brief Construct a new Einheit object
	 *
	 * @param name Der Name der Einheit.
	 * @param hp Wie viel Leben Sie hat.
	 * @param moral Die Moral der Einheit.
	 * @param starke Wie Stark sie ist.
	 * @param einsatzbereit Ob die Einheit Einsatzbereit ist.
	 * @param grosse Aus wie vielen Personen die Einheit besteht.
	 * @param xp Wie viel XP die Einheit hat.
	 */
	Einheit(std::string name, unsigned short int hp = 100,
		unsigned short int moral = 10, unsigned short int starke = 1,
		bool einsatzbereit = true, unsigned short int grosse = 1,
		unsigned int xp = 1);

	virtual ~Einheit();

	/**
	 * @brief Get the Name object
	 *
	 * @return std::string
	 */
	inline std::string getName() const
	{
		return Name;
	}

	/**
	 * @brief Get the Leben object
	 *
	 * @return int
	 */
	inline int getLeben() const
	{
		return HP;
	}

	/**
	 * @brief Get the Moral object
	 *
	 * @return int
	 */
	inline int getMoral() const
	{
		return Moral;
	}

	/**
	 * @brief Get the Starke object
	 *
	 * @return int
	 */
	inline int getStarke() const;

	/**
	 * @brief Get the Einsatzbereit object
	 *
	 * @return true
	 * @return false
	 */
	inline bool getEinsatzbereit() const
	{
		return Einsatzbereit;
	}

	/**
	 * @brief Get the Erfahrung object
	 *
	 * @return int
	 */
	inline int getErfahrung() const
	{
		return XP;
	}

	/**
	 * @brief Get the Level object
	 *
	 * @return int
	 */
	inline int getLevel() const
	{
		return Level;
	}

	/**
	 * @brief Fügt die Angebene Menge an Erfahrung der Einheit inzu.
	 *
	 * @param newXP Wie viel Erfahrung die Einheit erhalt.
	 */
	void xpHinzufugen(unsigned int newXP);
};

#endif /* EINHEIT_H_ */
