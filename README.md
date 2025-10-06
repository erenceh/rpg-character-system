# C++ RPG Character System
An object-oriented C++ RPG character system featuring classes, abilities, leveling, factions, and combat logic.

**Purpose:** This project was created to showcase **object-oriented programming (OOP) principles** such as encapsulation, inheritance, and modular design-while also applying design patterns like the **Factory pattern** for dynamic character and ability creation.

## Dependencies
- [nlohmann/json](https://github.com/nlohmann/json) (single header: `single_include/nlohmann/json.hpp`) for JSON parsing.

## Features

- **Character Classes & Stats**
	- Supports multiple classes: `WARRIOR`, `MAGE`, `RANGER`.
	- Each class has base stats (Health, Mana, Strength, Dexterity, Intelligence, Defense).
	- Modular `ClassFactory` allows dynamic class creation from JSON data.


- **Abilities & Combat**
	- Abilities include damage, mana cost, cooldowns, and status effects.
	- Target types: `SELF`, `ALLY_TARGET`, `ENEMY_TARGET`, `TARGET_UNKNOWN`.
	- Scalable damage based on character stats.
	- Full combat demo including attacks and ability usage.


- **Leveling & Experience**
	- Characters gain XP from combat.
	- Level-up increases stats based on class progression.
	- Automatic ability unlocks upon leveling.


- **Faction System**
	- Characters belong to factions: `PLAYER`, `ALLY_FACTION`, `ENEMY_FACTION`, `NEUTRAL`.
	- Combat rules depends on faction interactions.


- **JSON Data Integration**
	- Class stats, abilities, and XP progression are loaded dynamically from JSON files.
	- This project uses single_include/nlohmann/json.hpp for JSON parsing.
	- `JsonUtils` handles parsing and conversion.


## Design & Architecture

- **Object-Oriented**
	- `Character`, `Ability`, `Class` are separate classes with clear responsibilities.
	- Encapsulation of stats, abilities, and combat logic.


- **Factory Pattern**
	- `CharacterFactory` for dynamic character creation.
	- `AbilityFactory` for loading and assigning abilities.
	- `ClassFactory` for class stat management.


- **Extensible & Modular**
	- New classes and abilities can be added without modifying core code.
	- Easy to expand for RPG features like items and quests.


## Demo

Example usage from `main.cpp`:

```cpp
// Create characters
Character hero = CharacterFactory::createCharacterFromClass(PLAYER, "Player", WARRIOR, 1);
Character enemy = CharacterFactory::createCharacterFromClass(ENEMY_FACTION, "Skeleton Warrior", WARRIOR, 1);

// Leveling
hero.gainExperience(110);  // Level up and unlock new abilities

// Abilities
Ability fireball = AbilityFactory::getAbilitiesForCharacter(MAGE, 1)[0];
enemy.grantAbility(fireball);
enemy.useAbility("Fireball", hero);

// Combat
hero.basicAttack(enemy);
hero.useAbility("Power Strike", enemy);
```