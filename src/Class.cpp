#include "Class.h"

Class::Class()
	: classType(ClassType::CLASS_UNKNOWN),
	  baseHealth(0),
	  baseMana(0),
	  baseDefense(0),
	  baseStrength(0),
	  baseDexterity(0),
	  baseIntelligence(0) {
}

Class::Class(ClassType classType, int health, int mana, int defense, 
			 int strength, int dexterity, int intelligence)
	: classType{ classType },
	  baseHealth{ health },
	  baseMana{ mana },
	  baseDefense{ defense },
	  baseStrength{ strength },
	  baseDexterity{ dexterity },
	  baseIntelligence{ intelligence } {
}