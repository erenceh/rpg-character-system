#include "CharacterFactory.h"
#include "ClassFactory.h"

Character CharacterFactory::createCharacterFromClass(Faction faction, const std::string& name, 
													 ClassType classType, int level){
	Class classBlueprint = ClassFactory::getClass(classType);

	Character character = Character(
		faction,
		name,
		classBlueprint.getClassType(),
		level,
		classBlueprint.getBaseHealth(),
		classBlueprint.getBaseMana(),
		classBlueprint.getBaseDefense(),
		classBlueprint.getBaseStrength(),
		classBlueprint.getBaseDexterity(),
		classBlueprint.getBaseIntelligence()
		);
	return character;
}