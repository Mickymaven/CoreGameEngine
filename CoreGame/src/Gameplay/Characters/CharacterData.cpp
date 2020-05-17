#include "CharacterData.h"

vector<vector<AbilityName>> CharacterData::m_defaultAbilities;

CharacterData::CharacterData()
{
	if (m_defaultAbilities.size() <= 0) InitCharacterData();
}

void CharacterData::InitCharacterData()
{
	m_defaultAbilities.resize(characterNameCount);
	for (unsigned int i = 0; i < characterNameCount; i++)
	{
		m_defaultAbilities.at(i).resize(4);
	}

	m_defaultAbilities[characterAngryCat][0] = abilityCosmicSpaghetti;
	m_defaultAbilities[characterAngryCat][1] = abilityHuntOfTheHaunted;
	m_defaultAbilities[characterAngryCat][2] = abilitySpookySpaceMeringue;
	m_defaultAbilities[characterAngryCat][3] = abilityTheSlurpening;

	m_defaultAbilities[characterVisionOwl][0] = abilityCosmicSpaghetti;
	m_defaultAbilities[characterVisionOwl][1] = abilityHuntOfTheHaunted;
	m_defaultAbilities[characterVisionOwl][2] = abilitySpookySpaceMeringue;
	m_defaultAbilities[characterVisionOwl][3] = abilityTheSlurpening;

	m_defaultAbilities[characterNenian][0] = abilityValiantLeap;
	m_defaultAbilities[characterNenian][1] = abilityValiantLeap;
	m_defaultAbilities[characterNenian][2] = abilityEternalLight;
	m_defaultAbilities[characterNenian][3] = abilityElixirBurst;

	m_defaultAbilities[characterSurku][0] = abilityCosmicSpaghetti;
	m_defaultAbilities[characterSurku][1] = abilityEternalLight;
	m_defaultAbilities[characterSurku][2] = abilityElixirBurst;
	m_defaultAbilities[characterSurku][3] = abilityHiddenPower;

	m_defaultAbilities[characterGrey][0] = abilityCosmicSpaghetti;
	m_defaultAbilities[characterGrey][1] = abilityHuntOfTheHaunted;
	m_defaultAbilities[characterGrey][2] = abilitySpookySpaceMeringue;
	m_defaultAbilities[characterGrey][3] = abilityTheSlurpening;

	m_defaultAbilities[characterLoost][0] = abilityCosmicSpaghetti;
	m_defaultAbilities[characterLoost][1] = abilityHuntOfTheHaunted;
	m_defaultAbilities[characterLoost][2] = abilitySpookySpaceMeringue;
	m_defaultAbilities[characterLoost][3] = abilityTheSlurpening;

	m_defaultAbilities[characterTypy][0] = abilityCosmicSpaghetti;
	m_defaultAbilities[characterTypy][1] = abilityHuntOfTheHaunted;
	m_defaultAbilities[characterTypy][2] = abilitySpookySpaceMeringue;
	m_defaultAbilities[characterTypy][3] = abilityTheSlurpening;

	m_defaultAbilities[characterShork][0] = abilityAntiFireball;
	m_defaultAbilities[characterShork][1] = abilityMotoBoost;
	m_defaultAbilities[characterShork][2] = abilityEternalLight;
	m_defaultAbilities[characterShork][3] = abilityElixirBurst;

	m_defaultAbilities[characterCaalu][0] = abilityHealTurret;
	m_defaultAbilities[characterCaalu][1] = abilityHealTurret;
	m_defaultAbilities[characterCaalu][2] = abilityHealTurret;
	m_defaultAbilities[characterCaalu][3] = abilityHealTurret;

}
