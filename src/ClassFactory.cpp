#include "ClassFactory.h"
#include "JsonUtils.h"

std::map<ClassType, Class> ClassFactory::cachedClasses;
bool ClassFactory::isCacheLoaded = false;

void ClassFactory::ensureLoaded(const std::string& filename) {
	if (!isCacheLoaded) {
		loadAllClassTypes(filename);
		isCacheLoaded = true;
	}
}

void ClassFactory::loadAllClassTypes(const std::string& filename) {
	nlohmann::json classData = JsonUtils::loadJSON(filename);

	for (auto& [key, stats] : classData.items()) {
		ClassType type = JsonUtils::stringToClassType(key);

		Class newClass(
			type,
			JsonUtils::getIntFromJSON(stats, "maxHealth"),
			JsonUtils::getIntFromJSON(stats, "maxMana"),
			JsonUtils::getIntFromJSON(stats, "defense"),
			JsonUtils::getIntFromJSON(stats, "strength"),
			JsonUtils::getIntFromJSON(stats, "dexterity"),
			JsonUtils::getIntFromJSON(stats, "intelligence")
		);

		cachedClasses[type] = newClass;
	}
}

Class ClassFactory::getClass(ClassType classType) {
	ensureLoaded();

	auto it = cachedClasses.find(classType);
	if (it != cachedClasses.end()) {
		return it->second;
	}

	throw std::runtime_error("Class not found in ClassFactory");
}