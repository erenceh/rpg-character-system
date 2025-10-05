#include "Ability.h"
#include "Character.h"

// Constructor
Ability::Ability(const std::string& nameVal, int damageVal, int damageGrowthVal, int manaVal,
				 int manaGrowthVal, int cooldown, TargetType targetType, const std::string& statusEffect,
				 ClassType allowedClass, int minLevelVal)
	: name{ nameVal },
	  damage{ damageVal },
	  damageGrowth{ damageGrowthVal },
	  manaCost{ manaVal },
	  manaGrowth{ manaGrowthVal },
	  cooldown{ cooldown },
	  targetType{ targetType },
	  statusEffect{ statusEffect },
	  allowedClass{ allowedClass }, 
	  minLevel{ minLevelVal } {
}

// Copy Constructor
Ability::Ability(const Ability& other)
	: name(other.name),
	  damage(other.damage),
	  damageGrowth(other.damageGrowth),
	  manaCost(other.manaCost),
	  manaGrowth(other.manaGrowth),
	  cooldown(other.cooldown),
	  targetType(other.targetType),
	  statusEffect(other.statusEffect),
	  allowedClass(other.allowedClass),
	  minLevel(other.minLevel) {
}

int Ability::getEffectiveDamage(const Character& character) const {
	if (damageGrowth == 0) {
		return damage;
	}
	ClassType ctype = character.getCharacterClass();

	int scalingStat;
	switch (ctype) {
	case ClassType::MAGE: scalingStat = character.getIntelligence(); break;
	case ClassType::WARRIOR: scalingStat = character.getStrength(); break;
	case ClassType::RANGER: scalingStat = character.getDexterity(); break;
	default: scalingStat = 0; break;
	}

	return damage + static_cast<int>(scalingStat / damageGrowth);
}

int Ability::getEffectiveManaCost(int charLevel) const {
	return manaCost + (manaGrowth * ((charLevel - 1) / 5));
}

// Ability logic
void Ability::use(Character& user, Character& target) {
	if (!isAvailable()) {
		std::cout << name << " is on cooldown!" << std::endl;
		return;
	}

	int effectiveDamage = getEffectiveDamage(user);
	int effectiveMana = getEffectiveManaCost(user.getLevel());

	if (user.getCurrentMana() < manaCost) {
		std::cout << user.getName() << " doesn't have enough mana!" << std::endl;
		return;
	}

	switch (targetType) {
		case SELF:
			if (&user != &target) {
				std::cout << user.getName() << " can't use " << name << " on " << target.getName() << ". That ability can only be used on self!" << std::endl;
				std::cout << std::endl;
				return;
			}
			break;
		case ALLY_TARGET:
			if (user.getFaction() != target.getFaction() || &user == &target) {
				std::cout << user.getName() << " can't use " << name << " on " << target.getName() << ". That ability requires a valid ally!" << std::endl;
				std::cout << std::endl;
				return;
			}
			break;
		case ENEMY_TARGET:
			if (user.getFaction() == ENEMY_FACTION) {
				break;
			}
			if (target.getFaction() != ENEMY_FACTION) {
				std::cout << user.getName() << " can't use " << name << " on " << target.getName() << ". That ability requires an enemy!" << std::endl;
				std::cout << std::endl;
				return;
			}
			else {

			}
			break;
		default:
			std::cout << "Unknown target type for " << name << std::endl;
			return;
	}

	user.consumeMana(manaCost);

	std::cout << user.getName() << " used " << name << " on " << target.getName() << std::endl;
	std::cout << std::endl;

	switch (targetType) {
		case SELF:
			// Needs a Status Effect System to apply Self abilities
			// applySelfAbility();
			break;
		case ALLY_TARGET:
			// Needs a Status Effect System to apply Self abilities
			// applyAllyAbility();
			break;
		case ENEMY_TARGET:
			if (effectiveDamage > 0) {
				target.takeDamage(effectiveDamage, &user);
			}
	}
	startCooldown();
}

bool Ability::isAvailable() const {
	return currentCooldown == 0;
}

// Cooldown management
void Ability::startCooldown() {
	currentCooldown = cooldown;
}

void Ability::reduceCooldown() {
	if (currentCooldown > 0) {
		--currentCooldown;
	}
}

