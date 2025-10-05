#ifndef _JSONUTILS_H_
#define _JSONUTILS_H_

#include <nlohmann/json.hpp>
#include <string>
#include "Character.h"

class JsonUtils
{
public:
	static nlohmann::json loadJSON(const std::string& filePath);
	static std::string classTypeToString(ClassType classType);
	static ClassType stringToClassType(const std::string& classTypeStr);
	static std::string targetTypeToString(TargetType targetType);
	static TargetType stringToTargetType(const std::string& targetTypeStr);
	static int getIntFromJSON(const nlohmann::json& j, const std::string& key);
};

#endif // !_JSONUTILS_H_