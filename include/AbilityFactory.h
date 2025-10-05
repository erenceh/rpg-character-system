#ifndef _ABILITYFACTORY_H_
#define _ABILITYFACTORY_H_

#include <vector>
#include "Ability.h"

class AbilityFactory
{
private:
	static std::vector<Ability> cachedAbilities;
	static bool isCacheLoaded;

	static void ensureLoaded(const std::string& filename = "abilities.json");

public:
	static std::vector<Ability> loadAllAbilities(const std::string& filename = "abilities.json");
	static std::vector<Ability> getAbilitiesForCharacter(ClassType characterClass, int level);
};

#endif // !_ABILITYFACTORY_H_