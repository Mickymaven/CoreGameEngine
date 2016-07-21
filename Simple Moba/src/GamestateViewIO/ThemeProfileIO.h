#if !defined(THEMEPROFILEIO_H)
#define THEMEPROFILEIO_H

#include "../GamestateView/ThemeResourceProfile.h"
#include "ProfileIOBase.h"

#include "../../../CoreGame/src/Gameplay/Characters/CharacterClassName.h"

class ThemeProfileIO : public ProfileIOBase
{
protected:
	ThemeResourceProfile * themeResourceProfile;

public:
	ThemeProfileIO();
	~ThemeProfileIO();

	//bool WriteData(string path, vector<int> * binds);
	bool ReadData(string path, ThemeResourceProfile * themeResourceProfile);
};

#endif