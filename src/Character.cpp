#include <cmath>
#include "Character.h"
#include "JsonUtils.h"
#include "AbilityFactory.h"

// Constructors
Character::Character(Faction faction, std::string nameVal, ClassType characterClassType,
					 int levelVal, int maxHealthVal, int maxManaVal,
					 int defenseVal, int strengthVal, int dexterityVal, int intelligenceVal)
	: faction{ faction },
	  name{ nameVal }, 
	  characterClass{ characterClassType }, 
	  level{ levelVal },
	  maxHealth{ maxHealthVal }, 
	  maxMana{ maxManaVal }, 
	  defense{ defenseVal }, 
	  strength{ strengthVal }, 
	  dexterity{ dexterityVal },
	  intelligence{ intelligenceVal } {

	currentHealth = maxHealthVal;
	currentMana = maxManaVal;
	currentXP = 0;
	nextLevelXP = calculateNextLevelXP(levelVal);

	std::cout << name << " was created." << std::endl;
	std::cout << std::endl;

	learnNewAbilities();
}

// Destructor
Character::~Character() {

	// for debugging
	std::cout << "Character destructor called for: " << getName() << std::endl;
	std::cout << std::endl;
}

// Health management
void Character::takeDamage(int damageAmount, Character* opponent) {
	int armorDivisor = 30;  // controls diminishing returns for defense effectiveness
	double reduction = static_cast<double>(defense) / (defense + armorDivisor);
	int postDefDamage = static_cast<int>(std::floor(damageAmount * (1.0 - reduction)));
	int finalDamage = std::max(1, postDefDamage);
	currentHealth -= finalDamage;

	std::cout << name << " took " << finalDamage << " of damage!" << std::endl;
	std::cout << std::endl;

	if (currentHealth <= 0) {
		currentHealth = 0;
		if (!deathEventHandle && opponent) {
			deathTriggered(*opponent);
			deathEventHandle = true;
		}
	}
}

void Character::heal(int healAmount) {
	currentHealth += healAmount;
	if (currentHealth > maxHealth) {
		currentHealth = maxHealth;
	}
}

bool Character::isAlive() const {
	return currentHealth > 0;
}

void Character::deathTriggered(Character& opponent) {
	std::cout << name << " has died!" << std::endl;

	// give opponent xp
	int xpReward = calculateXPReward();
	opponent.gainExperience(xpReward);

	// can trigger other events such as drop loot, remove from combat, 
	// and remove from party as project grows
}

// Mana management
void Character::consumeMana(int consumeAmount) {
	currentMana -= consumeAmount;
	if (currentMana < 0) {
		currentMana = 0;
	}
}

void Character::restoreMana(int restoreAmount) {
	currentMana += restoreAmount;
	if (currentMana > maxMana) {
		currentMana = maxMana;
	}
}

// Level management & Stat progression
void Character::levelUp() {
	std::cout << "Level up! " << name << " reached level " << level << std::endl;
	std::cout << std::endl;
	level += 1;
	nextLevelXP = calculateNextLevelXP(level);
	increaseBaseStats();
	learnNewAbilities();
}

int Character::calculateNextLevelXP(int currentLevel) {
	static nlohmann::json xpData = JsonUtils::loadJSON("xp_table.json");
	
	// check for override first
	if (xpData.contains("overrides")) {
		auto overrides = xpData["overrides"];
		std::string key = std::to_string(currentLevel + 1);
		
		if (overrides.contains(key)) {
			return overrides[key];
		}
	}

	int base = xpData["formula"]["baseXP"];
	float multiplier = xpData["formula"]["xpMultiplier"];
	return static_cast<int>(base * std::pow(currentLevel, multiplier));
}

int Character::calculateXPReward() {
	int baseXP = 10;
	int levelFactor = level;
	int xpReward = baseXP * levelFactor;
	return std::max(1, xpReward);
}

void Character::gainExperience(int xpAmount) {
	std::cout << name << " gained " << xpAmount << "XP" << std::endl;
	std::cout << std::endl;

	currentXP += xpAmount;
	int tempXP = currentXP;

	while (currentXP >= nextLevelXP) {
		currentXP -= nextLevelXP;
		levelUp();
	}
}

void Character::increaseBaseStats() {
	static nlohmann::json classStatData = JsonUtils::loadJSON("class_stat_progression.json");
	std::string classKey = JsonUtils::classTypeToString(characterClass);
	nlohmann::json growth = classStatData[classKey];

	maxHealth += JsonUtils::getIntFromJSON(growth, "healthGain");
	maxMana += JsonUtils::getIntFromJSON(growth, "manaGain");
	strength += JsonUtils::getIntFromJSON(growth, "strengthGain");
	defense += JsonUtils::getIntFromJSON(growth, "defenseGain");
	dexterity += JsonUtils::getIntFromJSON(growth, "dexterityGain");
	intelligence += JsonUtils::getIntFromJSON(growth, "intelligenceGain");

	currentHealth = maxHealth;
	currentMana = maxMana;
}

// Combat management
void Character::basicAttack(Character& target) {
	bool canAttack = false;

	switch (faction) {
	case PLAYER:
	case ALLY_FACTION:
		// Player and allies can only attack enemies
		canAttack = (target.getFaction() == ENEMY_FACTION);
		break;
	case ENEMY_FACTION:
		// Enemies can attack anyone except other enemies
		canAttack = (target.getFaction() != ENEMY_FACTION);
		break;
	case NEUTRAL:
		// Neutral characters can't attack anyone
	default:
		canAttack = false;
		break;
	}

	if (!canAttack) {
		std::cout << name << " cannot attack " << target.getName() << ". Invalid target!" << std::endl;
		std::cout << std::endl;
		return;
	}
	int baseWeaponDamage{ 7 };  // example for weapon damage
	double statScale{ 0.9 };  // damage multiplier per stat point (controls scaling rate)

	int statValue;
	switch (characterClass) {
	case ClassType::MAGE: statValue = intelligence; break;
	case ClassType::WARRIOR: statValue = strength; break;
	case ClassType::RANGER: statValue = dexterity; break;
	default: statValue = 0; break;
	}

	int damage = baseWeaponDamage + floor(statValue * statScale);

	std::cout << name << " attacked " << target.getName() << std::endl;
	std::cout << std::endl;

	target.takeDamage(damage, this);
	
}

void Character::useAbility(const std::string& abilityName, Character& target) {
	for (auto& ability : abilities) {
		if (ability.getName() == abilityName) {
			ability.use(*this, target);
			return;
		}
	}
	std::cout << name << " does not know " << abilityName << "!" << std::endl;
	std::cout << std::endl;
}

// Ability management
void Character::learnNewAbilities() {
	std::vector<Ability> newAbilities = AbilityFactory::getAbilitiesForCharacter(characterClass, level);

	for (auto& ability : newAbilities) {
		if (!hasAbility(ability.getName())) {
			abilities.push_back(ability);
			std::cout << name << " has learned " << ability.getName() << std::endl;
			std::cout << std::endl;
		}
	}
}

void Character::grantAbility(const Ability& ability) {
	if (faction == PLAYER && characterClass != ability.getAllowedClass()) {
		std::cout << name << " can't learn " << ability.getName() << std::endl;
		std::cout << std::endl;
		return;
	}
	else if (level < ability.getMinLevel()) {
		std::cout << name << "'s level isn't high enough to learn " << ability.getName() << std::endl;
		std::cout << std::endl;
		return;
	}

	if (!hasAbility(ability.getName())) {
		abilities.push_back(ability);
		std::cout << name << " has been granted " << ability.getName() << std::endl;
	}
	std::cout << std::endl;
}

bool Character::hasAbility(const std::string& abilityName) const {
	for (auto& ability : abilities) {
		if (ability.getName() == abilityName) {
			return true;
		}
	}
	return false;
}

void Character::removeAbility(const std::string& abilityName) {
	for (auto it = abilities.begin(); it != abilities.end(); ++it) {
		if (it->getName() == abilityName) {
			abilities.erase(it);
			std::cout << abilityName << " was removed." << std::endl;
			std::cout << std::endl;
			break;
		}
	}
	std::cout << name << " doesn't have " << abilityName << " ability!" << std::endl;
	std::cout << std::endl;
}

// Display
void Character::displayStats() const {
	std::cout << "--- CHARACTER SHEET ---" << std::endl;
	std::cout << "Name: " << name << std::endl;
	std::cout << "Level: " << level << std::endl;
	std::cout << "Experience: " << currentXP << "/" << nextLevelXP << std::endl;
	std::cout << "Health: " << currentHealth << "/" << maxHealth << std::endl;
	std::cout << "Mana: " << currentMana << "/" << maxMana << std::endl;
	std::cout << "Defense: " << defense << std::endl;
	std::cout << "Strength: " << strength << std::endl;
	std::cout << "Dexterity: " << dexterity << std::endl;
	std::cout << "Intelligence: " << intelligence << std::endl;
	std::cout << "-----------------------" << std::endl;
	std::cout << std::endl;
}

void Character::displayAbilities() const {
	std::cout << "--- SPELLS & ABILITIES ---" << std::endl;
	for (auto& ability : abilities) {
		std::cout << ability.getName() << std::endl;
		std::cout << "\tDamage: " << ability.getDamage() << std::endl;
		std::cout << "\tMana Cost: " << ability.getManaCost() << std::endl;
		std::cout << "\tCooldown: " << ability.getCooldown() << std::endl;
		std::cout << "\tTarget Type: " << ability.getTargetType() << std::endl;
		std::cout << "\tStatus Effect: " << ability.getStatusEffect() << std::endl;
	}
	std::cout << "--------------------------" << std::endl;
	std::cout << std::endl;
}