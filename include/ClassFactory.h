#ifndef _CLASSFACTORY_H_
#define _CLASSFACTORY_H_

#include <map>
#include "Class.h"

class ClassFactory
{
private:
	static std::map<ClassType, Class> cachedClasses;
	static bool isCacheLoaded;

	static void ensureLoaded(const std::string& filename = "class_stats.json");

public:
	static void loadAllClassTypes(const std::string& filename = "class_stats.json");
	static Class getClass(ClassType classType);
};

#endif !_CLASSFACTORY_H_