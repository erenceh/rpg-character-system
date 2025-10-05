#include "JsonUtils.h"
#include <fstream>
#include <stdexcept>

nlohmann::json JsonUtils::loadJSON(const std::string& filePath) {
	std::ifstream inputFile("data/" + filePath);
	if (!inputFile.is_open()) {
		throw std::runtime_error("Could not open JSON file: " + filePath);
	}

	nlohmann::json jsonData;
	inputFile >> jsonData;
	return jsonData;
}

std::string JsonUtils::classTypeToString(ClassType classType) {
	switch (classType) {
		case MAGE: return "MAGE";
		case WARRIOR: return "WARRIOR";
		case RANGER: return "RANGER";
		default: return "UNKNOWN";
	}
}

ClassType JsonUtils::stringToClassType(const std::string& classTypeStr) {
	std::string lowerStr = classTypeStr;
	std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::toupper);
	if (classTypeStr == "MAGE") return MAGE;
	else if (classTypeStr == "WARRIOR") return WARRIOR;
	else if (classTypeStr == "RANGER") return RANGER;
	else return CLASS_UNKNOWN;
}

std::string JsonUtils::targetTypeToString(TargetType targetType) {
	switch (targetType) {
		case SELF: return "SELF";
		case ALLY_TARGET: return "ALLY_TARGET";
		case ENEMY_TARGET: return "ENEMY_TARGET";
		default: return "TARGET_UNKNOWN";
	}
}

TargetType JsonUtils::stringToTargetType(const std::string& targetTypeStr) {
	std::string lowerStr = targetTypeStr;
	std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::toupper);
	if (targetTypeStr == "SELF") return SELF;
	else if (targetTypeStr == "ALLY_TARGET") return ALLY_TARGET;
	else if (targetTypeStr == "ENEMY_TARGET") return ENEMY_TARGET;
	else return TARGET_UNKNOWN;
}

int JsonUtils::getIntFromJSON(const nlohmann::json& j, const std::string& key) {
	if (!j.contains(key)) throw std::runtime_error("Missing key: " + key);
	return j.contains(key) ? static_cast<int>(j[key].get<double>()) : 0;
}