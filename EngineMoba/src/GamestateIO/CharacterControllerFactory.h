#if !defined (CHARACTERCONTROLLERFACTORY_H)
#define CHARACTERCONTROLLERFACTORY_H

#include "GameObjectFactory.h"
#include "CharacterFactory.h"

class CharacterControllerFactory : public GameObjectFactory
{
protected:
	CharacterFactory * m_characterFactory;
	Character * m_constructedCharacter;

public:

};

#endif