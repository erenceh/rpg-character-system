#ifndef _CLASS_H_
#define _CLASS_H_

#include <string>
#include <vector>
#include "Enums.h"

class Character;

class Class
{
private:
	ClassType classType;
	int baseHealth;
	int baseMana;
	int baseDefense;
	int baseStrength;
	int baseDexterity;
	int baseIntelligence;

public:
	// Constructor
	Class();

	Class(ClassType classType, int health, int mana,
		  int defense, int strength, int dexterity,
		  int intelligence);

	// Getters
	ClassType getClassType() const { return classType; }
	int getBaseHealth() const { return baseHealth; }
	int getBaseMana() const { return baseMana; }
	int getBaseDefense() const { return baseDefense; }
	int getBaseStrength() const { return baseStrength; }
	int getBaseDexterity() const { return baseDexterity; }
	int getBaseIntelligence() const { return baseIntelligence; }
};

#endif // !_CLASS_H_