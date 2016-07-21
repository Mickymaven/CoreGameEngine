#if !defined(INDICATORCONTROLLER_H)
#define INDICATORCONTROLLER_H


#include "../../../EngineMoba/src/Actor_Control/InteractionZone.h"
#include "../../../EngineGameModuleDirectX9/src/UI/FontGroup.h"
#include "../../../EngineGameModuleDirectX9/src/Graphics/Billboard.h"
#include "../ViewControl/CameraDirector.h"
#include "../UI/GameCursor.h"


class IndicatorController
{
private:
	MobaState * gameState;

	CameraDirector * cameraDirector;

	GameCursor * m_cursor;

	FontGroup * m_fontGroup;

	SpriteView * m_groundView;

	char m_buffer50[50];
	RECT m_fontPOS;


	D3DXVECTOR3 point1;
	D3DXVECTOR3 point2;
	D3DXVECTOR4 m_ResultPoint;

	LMVector3 * m_tempCharacterPos;
	float m_tempRadians;

	//temp ///////
	vector <ShopZone*> * zones;
	ShopZone * zone;


	vector<Interaction*> * m_interactions;
	vector<InteractionZone*> * m_interactionZones;
	InteractionZone * m_interactionZone;
	/////////

	Billboard m_shopRangeIndicator;

	Billboard m_rangeIndicator;
	Billboard m_directionalIndicator;
	Billboard m_pointIndicator;
	Billboard m_walkIndicator;

	LMVector3 m_indicatorDirectionVector;
	LMVector3 m_MousePointVector;

	LMVector3 m_tempVec3;

	float m_walkIndicatorLife;
	float m_walkIndicatorTimer;

public:
	IndicatorController();
	~IndicatorController();

	bool Init(MobaState * state, CameraDirector * cameraDir, GameCursor * cursor, FontGroup * fontGroup, SpriteView * groundView);

	bool CalcResultPointGround();
	
	void Update(float deltaTime);

	void RenderDebugRanges();
	void RenderShopZones();

	void UpdateIndicators(float deltaTime, float gameTime, Actor *  actor);
	void UpdateRangeIndicator();
	void UpdateRangeIndicatorWithAbility(Ability * abilityCasting);

	void RenderRangeIndicator();
	void RenderRangeIndicator(AbilityCastType castType);
	void RenderIndicators();

	Billboard * GetShopRangeIndicator();

	Billboard * GetRangeIndicator();
	Billboard * GetDirectionalIndicator();
	Billboard * GetPointIndicator();
	Billboard * GetWalkIndicator();

	LMVector3 * GetIndicatorDirectionVector();
	LMVector3 * GetMousePointVector();

	float * GetWalkIndicatorLife();
	float * GetWalkIndicatorTimer();

	void SetWalkIndicatorTimer(float seconds);

};

#endif