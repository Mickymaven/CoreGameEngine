#if !defined(CHARACTERDATA_H)
#define CHARACTERDATA_H

#include <vector>
using std::vector;

#include "../Abilities/AbilityName.h"
#include "CharacterClassName.h"

struct CharacterData
{
	static vector<vector<AbilityName>> m_defaultAbilities;

	CharacterData();
	void InitCharacterData();

};

#endif