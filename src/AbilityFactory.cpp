#include "AbilityFactory.h"
#include "JsonUtils.h"

std::vector<Ability> AbilityFactory::cachedAbilities;
bool AbilityFactory::isCacheLoaded = false;

void AbilityFactory::ensureLoaded(const std::string& filename) {
	if (!isCacheLoaded) {
		cachedAbilities = loadAllAbilities(filename);
		isCacheLoaded = true;
	}
}

std::vector<Ability> AbilityFactory::loadAllAbilities(const std::string& filename) {
	std::vector<Ability> abilities;
	nlohmann::json abilityData = JsonUtils::loadJSON(filename);

	for (auto& abilityJson : abilityData) {
		Ability ab(
			abilityJson["name"].get<std::string>(),
			JsonUtils::getIntFromJSON(abilityJson, "damage"),
			JsonUtils::getIntFromJSON(abilityJson, "damageGrowth"),
			JsonUtils::getIntFromJSON(abilityJson, "manaCost"),
			JsonUtils::getIntFromJSON(abilityJson, "manaGrowth"),
			JsonUtils::getIntFromJSON(abilityJson, "cooldown"),
			JsonUtils::stringToTargetType(abilityJson["targetType"]),
			abilityJson["statusEffect"].get<std::string>(),
			JsonUtils::stringToClassType(abilityJson["allowedClass"]),
			JsonUtils::getIntFromJSON(abilityJson, "minLevel")
		);

		cachedAbilities.push_back(ab);
	}

	isCacheLoaded = true;
	return cachedAbilities;
}

std::vector<Ability> AbilityFactory::getAbilitiesForCharacter(ClassType characterClass, int level) {
	ensureLoaded();
	std::vector<Ability> filtered;

	for (auto& ability : cachedAbilities) {
		// Check minimum level and character class
		if (ability.getMinLevel() <= level && ability.getAllowedClass() == characterClass) {
			filtered.push_back(ability);
		}
	}

	return filtered;
}