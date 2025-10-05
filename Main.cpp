#include <iostream>
#include "Character.h"
#include "CharacterFactory.h"
#include "AbilityFactory.h"

#include <fstream>
#include <filesystem>

void printHealth(Character& character);
void printMana(Character& character);
void printXP(Character& character);

int main() {
	std::cout << std::boolalpha << std::endl;

	// Character creation Demo
	std::cout << "=============== Character Creation Demo ===============\n" << std::endl;
	Character hero1 = CharacterFactory::createCharacterFromClass(PLAYER, "Player", WARRIOR, 1);
	hero1.displayStats();
	hero1.displayAbilities();

	Character enemy1 = CharacterFactory::createCharacterFromClass(ENEMY_FACTION, "Skeleton Warrior", WARRIOR, 1);
	enemy1.displayStats();
	enemy1.displayAbilities();

	// Leveling Demo
	std::cout << "=============== Leveling Demo ===============\n" << std::endl;
	hero1.gainExperience(90);
	printXP(hero1);

	hero1.gainExperience(20);
	printXP(hero1);

	hero1.displayStats();
	hero1.displayAbilities();

	// Abilities Demo
	std::cout << "=============== Abilities Demo ===============\n" << std::endl;
	hero1.removeAbility("Rend");
	hero1.displayAbilities();
	hero1.removeAbility("Fireball");

	Ability fireball = AbilityFactory::getAbilitiesForCharacter(MAGE, 1)[0];
	hero1.grantAbility(fireball);

	std::cout << "Player has Power Strike ability: " << hero1.hasAbility("Power Strike") << std::endl;
	std::cout << std::endl;

	std::cout << "Player has Rend ability: " << hero1.hasAbility("Rend") << std::endl;
	std::cout << std::endl;

	Ability rend = AbilityFactory::getAbilitiesForCharacter(WARRIOR, 2)[1];
	hero1.grantAbility(rend);

	std::cout << "Player has Rend ability: " << hero1.hasAbility("Rend") << std::endl;
	std::cout << std::endl;

	hero1.displayAbilities();

	Ability rage = AbilityFactory::getAbilitiesForCharacter(WARRIOR, 4)[2];
	hero1.grantAbility(rage);

	hero1.displayStats();
	hero1.gainExperience(800);
	hero1.displayStats();
	hero1.displayAbilities();

	enemy1.grantAbility(fireball);
	enemy1.displayAbilities();

	// Combat Demo
	std::cout << "=============== Combat Demo ===============\n" << std::endl;
	hero1.basicAttack(enemy1);
	printHealth(enemy1);

	hero1.useAbility("Rend", enemy1);
	printHealth(enemy1);

	enemy1.setMaxMana(100);
	enemy1.setCurrentMana(100);
	enemy1.useAbility("Fireball", hero1);
	printHealth(hero1);

	Character hero2 = CharacterFactory::createCharacterFromClass(ALLY_FACTION, "Gandolf", MAGE, 1);
	hero1.useAbility("Power Strike", hero2);

	enemy1.basicAttack(hero2);
	printHealth(hero2);

	Character npc1 = CharacterFactory::createCharacterFromClass(NEUTRAL, "Shop Keeper", CLASS_UNKNOWN, 1);
	hero2.basicAttack(npc1);
	hero2.useAbility("Fireball", npc1);

	npc1.basicAttack(hero2);
	npc1.basicAttack(enemy1);

	enemy1.basicAttack(npc1);

	hero1.setCurrentMana(hero1.getMaxMana());
	printMana(hero1);
	hero1.useAbility("Rage", hero2);
	hero1.useAbility("Rage", npc1);
	hero1.useAbility("Rage", enemy1);
	hero1.useAbility("Rage", hero1);

	printXP(hero1);

	enemy1.setCurrentHealth(1);
	hero1.basicAttack(enemy1);

	printXP(hero1);
	hero1.displayStats();

	Character enemy2 = CharacterFactory::createCharacterFromClass(ENEMY_FACTION, "Skeleton Archer", RANGER, 7);
	enemy2.displayStats();

	enemy2.setCurrentHealth(1);
	hero1.basicAttack(enemy2);

	hero1.displayStats();

	std::cin.get();
	//return 0;
}

void printHealth(Character& character) {
	std::cout << character.getName() << "'s HP: " << character.getCurrentHealth() << "/" << character.getMaxHealth() << std::endl;
	std::cout << std::endl;
}

void printMana(Character& character) {
	std::cout << character.getName() << "'s MP: " << character.getCurrentMana() << "/" << character.getMaxMana() << std::endl;
	std::cout << std::endl;
}

void printXP(Character& character) {
	std::cout << character.getName() << "'s XP: " << character.getCurrentXP() << "/" << character.getNextLevelXP() << std::endl;
	std::cout << std::endl;
}
