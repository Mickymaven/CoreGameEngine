#include "IndicatorController.h"


IndicatorController::IndicatorController()
{

}

IndicatorController::~IndicatorController()
{

}

bool IndicatorController::Init(MobaState * state, CameraDirector * cameraDir, GameCursor * cursor, FontGroup * fontGroup, SpriteView * groundView)
{
	m_groundView = groundView;
	gameState = state;
	cameraDirector = cameraDir;
	m_cursor = cursor;

	m_fontGroup = fontGroup;


	m_tempCharacterPos = nullptr;

	m_fontPOS = { 0, 50, g_clientSizeRect->right, g_clientSizeRect->bottom };
	
	if (!m_shopRangeIndicator.Init(g_D3D_Device, "Resources/misc/range-indicator.png", billboardAlignMiddleCentre,1.0f, 1.0f)) return false;
	if (!m_rangeIndicator.Init(g_D3D_Device, "Resources/misc/range-indicator.png", billboardAlignMiddleCentre, 1.0f, 1.0f)) return false;
	if (!m_directionalIndicator.Init(g_D3D_Device, "Resources/misc/directional-cast-indicator.png", billboardAlignBottomCentre, 6.0f, 6.0f)) return false;
	if (!m_pointIndicator.Init(g_D3D_Device, "Resources/misc/point-cast-indicator.png", billboardAlignMiddleCentre, 6.0f, 6.0f)) return false;
	if (!m_walkIndicator.Init(g_D3D_Device, "Resources/misc/walk-indicator.png", billboardAlignMiddleCentre,20.0f, 20.0f)) return false;

	m_walkIndicatorLife = 10.8f;
	m_walkIndicatorTimer = 0.0f;


	m_walkIndicator.GetPhysicsObject()->GetPosition()->y = 0.2f;

	return true;
}


void IndicatorController::Update(float deltaTime)
{
	



}

void IndicatorController::RenderDebugRanges()
{
	m_interactions = nullptr;
	m_interactionZones = nullptr;
	m_interactionZone = nullptr;

	for (unsigned int i = 0; i < gameState->GetNeutralTargetControllers()->size(); i++)
	{
		m_interactions = gameState->GetNeutralTargetControllers()->at(i)->GetInteractions();

		for (unsigned int j = 0; j < m_interactions->size(); j++)
		{
			m_interactionZones = gameState->GetNeutralTargetControllers()->at(i)->GetInteractions()->at(j)->GetInteractionZones();

			for (unsigned int k = 0; k < m_interactionZones->size(); k++)
			{
				m_interactionZone = m_interactionZones->at(k);

				m_shopRangeIndicator.GetPhysicsObject()->GetPosition()->x = m_interactionZone->GetPosition()->x;
				m_shopRangeIndicator.GetPhysicsObject()->GetPosition()->y = 0.3f;
				m_shopRangeIndicator.GetPhysicsObject()->GetPosition()->z = m_interactionZone->GetPosition()->z;
				m_shopRangeIndicator.SetRadius(m_interactionZone->GetRadius());
				m_shopRangeIndicator.Render();
			}
		}
	}
}

void IndicatorController::RenderShopZones()
{
	zones = NULL;
	zone = NULL;

	for (unsigned int i = 0; i < gameState->GetShops()->size(); i++)
	{
		zones = gameState->GetShops()->at(i).GetShopZones();

		for (unsigned int z = 0; z < zones->size(); z++)
		{
			zone = gameState->GetShops()->at(i).GetShopZones()->at(z);

			if (zone->GetIsVisibleThisUpdate())
			{
				//render
				sprintf_s(m_buffer50, zone->GetName()->c_str());
				m_fontGroup->m_font->DrawText(NULL, m_buffer50, -1, &m_fontPOS, DT_CENTER, D3DCOLOR_XRGB(220, 200, 255));

				//shop zone range indicator
				m_shopRangeIndicator.GetPhysicsObject()->GetPosition()->x = zone->GetPosition()->x;
				m_shopRangeIndicator.GetPhysicsObject()->GetPosition()->z = zone->GetPosition()->z;
				m_shopRangeIndicator.SetRadius(zone->GetRadius());
				m_shopRangeIndicator.Render();
			}
		}
	}	
}

void IndicatorController::UpdateIndicators(float deltaTime, float gameTime, Actor * actor)
{
	// PlayerInputController::UpdateIndicators
	// update indicators in based on player state

	ActorState state = actor->GetState();

	switch (state)
	{
	case actorUnspawned:
		break;
	case actorDead:
		break;
	case actorRecall:
		break;
	case actorCasting:
		break;
	case actorBasicAttack:
		break;
	case actorStationary:
		break;
	case actorWalking:
		break;
	case actorDirectionalCast:
		UpdateRangeIndicator();

		

		if (CalcResultPointGround())
		{
			m_tempCharacterPos = actor->GetPhysicsObject()->GetPosition();

			//set indicator direction to the displacement from the target
			m_indicatorDirectionVector.x = m_ResultPoint.x - m_tempCharacterPos->x;
			m_indicatorDirectionVector.y = 0.0f;
			m_indicatorDirectionVector.z = m_ResultPoint.z - m_tempCharacterPos->z;
			m_indicatorDirectionVector.Normalize();

			m_tempRadians = atan2(m_indicatorDirectionVector.x, m_indicatorDirectionVector.z);


			m_tempVec3.x = m_tempCharacterPos->x;
			m_tempVec3.y = 0.3f;
			m_tempVec3.z = m_tempCharacterPos->z;


			m_directionalIndicator.GetPhysicsObject()->SetPosition(m_tempVec3);

			m_directionalIndicator.GetPhysicsObject()->GetRotation()->x = m_tempRadians;
			//, 0.0f, 0.0f));

		}//endif



		//1. get ray from  our mouse coords

		//2. get an interscetion with a mesh and returns the interect point
		//in the world coords.


		//3.  re calc all the matrix transformation stuff of our directional indicator
		// (intersection, players position)
		//+0.3f to y ccoord





		break;
	case actorInstantCast:
		//no indicator update stuff


		break;
	case actorPointCast:
		//1. get ray from  our mouse coords

		//2. get an interscetion with a  terrain mesh and returns the interect point
		//in the world coords.


		//3.  re calc all the matrix transformation stuff of our directional indicator
		// (intersection, players position)
		//just setting the indicator to the intersect point +0.3f to y ccoord


		//it can only be cast as far as our ability range allows
		//if the intersection point is less then the ability range
		//we show the ability at the point
		//if its not have a range indicator appear a different color to let player know they
		// are pointing their indicator out side of the rage

		UpdateRangeIndicator();

		if (CalcResultPointGround())
		{
			m_MousePointVector.x = m_ResultPoint.x;
			m_MousePointVector.y = m_ResultPoint.y;
			m_MousePointVector.z = m_ResultPoint.z;

			m_tempVec3.x = m_ResultPoint.x;
			m_tempVec3.y = 0.3f;
			m_tempVec3.z = m_ResultPoint.z;

			m_pointIndicator.GetPhysicsObject()->SetPosition(m_tempVec3);


		}

		break;
	case actorSingleTargetCast:

		UpdateRangeIndicator();

		//update stuff



		/// STUFF WE DO IN CURSOR CONTROLLER THAT COULD BE SHARED
		/// eg to select a more colorful range indicator if you are mousing a target in range and ability is off cooldown


		// 1. get ray from  our mouse coords
		//method 1:
		// 2. get an interscetion with the first each valid enemy meshes and returns


		//if no actors were intersected we save th knowledge and later
		//we render a "not selected type single target cast indicator".

		//if there was at least one intersection, then show  a "valid target
		//aka yeah "buddy you can click the shit out of them now indicator"




		break;
	case actorStateCount:
		break;
	default:
		break;
	}


	
	if (gameState->GetControlledCharacter()->GetWalkState()->GetState() == walkStateWalking)
	{
		SetWalkIndicatorTimer(m_walkIndicatorTimer + deltaTime);
	}

	else
	{
		SetWalkIndicatorTimer(0.0f);
	}
}

void IndicatorController::UpdateRangeIndicator()
{
	// could potentially only happen once upon character casts

	Ability * abilityCasting = gameState->GetControlledCharacter()->ReturnCastingAbility();

	if (abilityCasting != nullptr)
	{
		UpdateRangeIndicatorWithAbility(abilityCasting);
	}
}

void IndicatorController::UpdateRangeIndicatorWithAbility(Ability * abilityCasting)
{

	if (abilityCasting != NULL)
	{
		GetRangeIndicator()->SetRadius(abilityCasting->GetRange());
	}

	m_tempCharacterPos = gameState->GetControlledActor()->GetPhysicsObject()->GetPosition();

	m_rangeIndicator.GetPhysicsObject()->GetPosition()->x = m_tempCharacterPos->x;
	m_rangeIndicator.GetPhysicsObject()->GetPosition()->y = 0.25f;
	m_rangeIndicator.GetPhysicsObject()->GetPosition()->z = m_tempCharacterPos->z;

}

bool IndicatorController::CalcResultPointGround()
{
	GetRayFromLMCamera(
		cameraDirector->GetPointerToCurrentCamera(),
		g_mouseClientPosition.x,
		g_mouseClientPosition.y,
		point1,
		point2);

	 return PickFromSprite(&m_ResultPoint, m_groundView->GetLMMesh(), point1, point2);
}

void IndicatorController::RenderRangeIndicator()
{
	switch (gameState->GetControlledCharacter()->GetActor()->GetState())
	{
	case actorDirectionalCast:
		m_rangeIndicator.Render();

		break;
	case actorPointCast:
		m_rangeIndicator.Render();

		break;
	case actorSingleTargetCast:
		if (m_cursor->GetState() == gameCursorTypeCastAttack)
		{
			m_rangeIndicator.Render();
			m_rangeIndicator.Render();

		}

		m_rangeIndicator.Render();
		break;
	default:
		break;
	}
}

void IndicatorController::RenderRangeIndicator(AbilityCastType castType)
{
	switch (castType)
	{
	case abilityCastTypeDirectionalCast:
		m_rangeIndicator.Render();

		break;
	case abilityCastTypePointCast:
		m_rangeIndicator.Render();

		break;
	case abilityCastTypeSingleTargetCast:
		m_rangeIndicator.Render();


		break;
	default:
		break;
	}
}

void IndicatorController::RenderIndicators()
{

	g_D3D_Device->SetRenderState(D3DRS_ZENABLE, TRUE);



	if (m_walkIndicatorTimer < m_walkIndicatorLife)
	{
		if (m_walkIndicatorTimer > 0.0f)
		{
			m_walkIndicator.Render();
		}
	}

	switch (gameState->GetControlledCharacter()->GetActor()->GetState())
	{
	case actorDirectionalCast:
		m_directionalIndicator.Render();
		break;
	case actorPointCast:
		m_pointIndicator.Render();
		break;
	case actorSingleTargetCast:
		break;
	default:
		break;
	}

	

	g_D3D_Device->SetRenderState(D3DRS_ZENABLE, FALSE);
}

Billboard * IndicatorController::GetShopRangeIndicator()
{
	return &m_shopRangeIndicator;
}

Billboard * IndicatorController::GetRangeIndicator()
{
	return  &m_rangeIndicator;
}

Billboard * IndicatorController::GetDirectionalIndicator()
{
	return  &m_directionalIndicator;
}

Billboard * IndicatorController::GetPointIndicator()
{
	return  &m_pointIndicator;
}

Billboard * IndicatorController::GetWalkIndicator()
{
	return  &m_walkIndicator;
}

LMVector3 * IndicatorController::GetIndicatorDirectionVector()
{
	return &m_indicatorDirectionVector;
}

LMVector3 * IndicatorController::GetMousePointVector()
{
	return &m_MousePointVector;
}

float * IndicatorController::GetWalkIndicatorTimer()
{
	return &m_walkIndicatorTimer;
}

float * IndicatorController::GetWalkIndicatorLife()
{
	return &m_walkIndicatorLife;
}

void IndicatorController::SetWalkIndicatorTimer(float seconds)
{

	m_walkIndicatorTimer = seconds;
}