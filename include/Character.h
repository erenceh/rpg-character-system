#ifndef _CHARACTER_H_
#define _CHARACTER_H_
#include <iostream>
#include <string>
#include <vector>
#include "Ability.h"
#include "Enums.h"

class Character
{
private:
	Faction faction;
	std::string name;
	ClassType characterClass;
	int level;
	int maxHealth;
	int currentHealth;
	int maxMana;
	int currentMana;
	int defense;
	int strength;
	int dexterity;
	int intelligence;

	int currentXP;
	int nextLevelXP;
	std::vector<Ability> abilities;
	bool deathEventHandle = false;

public:
	// Constructor
	Character(Faction faction, std::string nameVal, ClassType characterClassType,
			  int levelVal, int maxHealthVal, int maxManaVal, 
			  int defenseVal, int strengthVal, int dexterityVal, int intelligenceVal);

	// Destructor
	~Character();
	
	// Getters
	Faction getFaction() const { return faction; }
	const std::string& getName() const { return name; }
	ClassType getCharacterClass() const { return characterClass; }
	int getLevel() const { return level; }
	int getMaxHealth() { return maxHealth; }
	int getCurrentHealth() const { return currentHealth; }
	int getMaxMana() const { return maxMana; }
	int getCurrentMana() const { return currentMana; }
	int getDefense() const { return defense; }
	int getStrength() const { return strength; }
	int getDexterity() const { return dexterity; }
	int getIntelligence() const { return intelligence; }
	int getCurrentXP() const { return currentXP; }
	int getNextLevelXP() const { return nextLevelXP; }
	const std::vector<Ability>& getAbilities() const { return abilities; }

	// Setters
	void setName(const std::string& newName) { name = newName; }
	void setMaxHealth(int maxHealthVal) { maxHealth = maxHealthVal; }
	void setCurrentHealth(int currentHealthVal) { currentHealth = currentHealthVal; }
	void setMaxMana(int maxManaVal) { maxMana = maxManaVal; }
	void setCurrentMana(int currentManaVal) { currentMana = currentManaVal; }
	void setDefense(int defenseVal) { defense = defenseVal; }
	void setStrength(int strengthVal) { strength = strengthVal; }
	void setDexterity(int dexterityVal) { dexterity = dexterityVal; }
	void setIntelligence(int intelligenceVal) { intelligence = intelligenceVal; }

	// Health management
	void takeDamage(int damageAmount, Character* opponent);
	void heal(int healAmount);
	bool isAlive() const;
	void deathTriggered(Character& opponent);

	// Mana management
	void consumeMana(int consumeAmount);
	void restoreMana(int restoreAmount);

	// Level management & Stat progression
	void levelUp();
	int calculateNextLevelXP(int currentLevel);
	int calculateXPReward();
	void gainExperience(int xpAmount);
	void increaseBaseStats();

	// Combat management
	void basicAttack(Character& target);
	void useAbility(const std::string& abilityName, Character& target);

	// Ability management
	void learnNewAbilities();
	void grantAbility(const Ability& ability);
	bool hasAbility(const std::string& abilityName) const;
	void removeAbility(const std::string& abilityName);

	// Display
	void displayStats() const;
	void displayAbilities() const;
};

#endif // !_CHARACTER_H_

