#ifndef _ABILITY_H_
#define _ABILITY_H_

#include <string>
#include "Enums.h"

class Character;

class Ability
{
private:
	std::string name;
	int damage;
	int damageGrowth;
	int manaCost;
	int manaGrowth;
	int cooldown;
	TargetType targetType;
	std::string statusEffect;
	ClassType allowedClass;
	int minLevel;

	int currentCooldown = 0;

public:
	// Constructor
	Ability(const std::string& nameVal, int damageVal, int damageGrowthVal, int manaVal, 
		    int manaGrowthVal, int cooldown, TargetType targetType, const std::string& statusEffect, 
			ClassType allowedClass, int minLevelVal);

	// Copy Constructor
	Ability(const Ability& other);

	// Getters
	std::string getName() const { return name; }
	int getDamage() const { return damage; }
	int getDamageGrowth() const { return damageGrowth; }
	int getManaCost() const { return manaCost; }
	int getManaGrowth() const { return manaGrowth; }
	int getCooldown() const { return cooldown; }
	int getCurrentCooldown() const { return currentCooldown; }
	TargetType getTargetType() const { return targetType; }
	std::string getStatusEffect() const { return statusEffect; }
	ClassType getAllowedClass() const { return allowedClass; }
	int getMinLevel() const { return minLevel; }

	int getEffectiveDamage(const Character& character) const;
	int getEffectiveManaCost(int charLevel) const;

	// Ability logic
	void use(Character& user, Character& target);
	bool isAvailable() const;

	// Cooldown management
	void startCooldown();
	void reduceCooldown();
};

#endif // !_ABILITY_H_

