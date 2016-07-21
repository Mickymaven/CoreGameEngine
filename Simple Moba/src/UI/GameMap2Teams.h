#if !defined(GAMEMAP2TEAMS_H)
#define GAMEMAP2TEAMS_H

#include "UIMobaMap.h"

class GameMap2Teams: public UIMobaMap
{
private:

public:
	GameMap2Teams();
	~GameMap2Teams();
	bool Init();
	void Update(float deltaTime);
	void Render();
};

#endif