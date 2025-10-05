#ifndef _CHARACTERFACTORY_H_
#define _CHARACTERFACTORY_H_

#include "Character.h"

class CharacterFactory
{
public:
	static Character createCharacterFromClass(Faction faction, const std::string& name, 
											  ClassType classType, int level);
};

#endif // !