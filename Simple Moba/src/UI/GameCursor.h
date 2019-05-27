#if !defined(GAMECURSOR_H)
#define GAMECURSOR_H

#include <vector>
using std::vector;

#include "../../../EngineGameModuleDirectX9/src/UI/UIElement.h"

#include "../../../EngineGamePlatform/src/Application/Globals.h"//todo BAD!


enum GameCursorTypes
{
	gameCursorTypeNone,

	gameCursorTypeCursor,
	gameCursorTypeCameraPan,
	gameCursorTypeTradeInfo,

	gameCursorTypeInfo,
	gameCursorTypeInfoAttack,

	gameCursorDirectional,
	gameCursorDirectionalAttack,

	gameCursorTypeCast,
	gameCursorTypeCastAttack,

	gameCursorTypePoint,
	gameCursorTypePointAttack,

	gameCursorTypeCooldownCastAttack,
	gameCursorTypeCooldownAttack,
	gameCursorTypeCooldownCast,

	gameCursorTypeRangeAttack,
	gameCursorTypeRange,

	gameCursorTypeAttackMove,
	
	gameCursorTypeHeal,
	gameCursorTypeHealCast,

	
	gameCursorTypeCount
};

class GameCursor : public UIElement
{
private:

protected:
	GameCursorTypes m_state;

	vector<string> m_paths;
	vector<LPDIRECT3DTEXTURE9> m_textures;

public:
	GameCursor();
	~GameCursor();

	bool Init(float width, float height);

	void Update(float delaTime);
	void Render();

	GameCursorTypes GetState();

	void SetState(GameCursorTypes cursorType);
	

	//GameCursorTypes WhichCursorShouldIShow(MobaState * gameState);
};

#endif