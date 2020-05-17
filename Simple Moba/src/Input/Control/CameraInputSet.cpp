#include "CameraInputSet.h"


CameraInputSet::CameraInputSet() : InputSet()
{
}

CameraInputSet::CameraInputSet(StandardMatch5v5State * state, MobaViewState * view) : InputSet()
{
	gameState = state;
	gameView = view;
	m_cameraDirector = view->GetCameraDirector();
}

CameraInputSet::~CameraInputSet()
{

}

void CameraInputSet::Update(float deltaTime)
{




}

void CameraInputSet::AttemptAction(int action, float deltaTime)
{
	switch (action)
	{
		
	case cameraActionCameraPanModifier: 
		if ( false == sm_gameInputController->GetMousePress(RIGHT_BUTTON,TRUE,TRUE) )
		{
			m_cameraDirector->CameraPanBehavior(
				sm_gameInputController->GetMousePressDownLast(MIDDLE_BUTTON), deltaTime);
		}
		break;

	case cameraActionToggleCameraLock:
		m_cameraDirector->ActionToggleCameraLock(gameState->GetControlledActor());
		break;

	case cameraActionCentreCamera:
		
		if (!m_cameraDirector->GetIsCameraLocked())
		{
			m_cameraDirector->CentreCameraAfterPlayerUpdate();
		} //Function below UpdateCameraStatesAfterPlayerMovement
		  //that is meant to get called in Game Loop

		if (m_cameraDirector->GetUsingCamera() == usingThirdPersonCamera)
		{
			m_cameraDirector->CentreThirdPersonCam(gameState->GetControlledActor());
		}

		 break;
	
	case cameraActionCameraFocusPlayer1:gameView->ActionSetControlledPlayerView(0);break;
	case cameraActionCameraFocusPlayer2:gameView->ActionSetControlledPlayerView(1);break;
	case cameraActionCameraFocusPlayer3:gameView->ActionSetControlledPlayerView(2);break;
	case cameraActionCameraFocusPlayer4:gameView->ActionSetControlledPlayerView(3);break;
	case cameraActionCameraFocusPlayer5:gameView->ActionSetControlledPlayerView(4);break;
	case cameraActionCameraFocusPlayer6:gameView->ActionSetControlledPlayerView(5);break;
	case cameraActionCameraFocusPlayer7:gameView->ActionSetControlledPlayerView(6);break;
	case cameraActionCameraFocusPlayer8:gameView->ActionSetControlledPlayerView(7);break;
	case cameraActionCameraFocusPlayer9:gameView->ActionSetControlledPlayerView(8);break;
	case cameraActionCameraFocusPlayer10:gameView->ActionSetControlledPlayerView(9);break;
	case cameraActionCameraFocusPlayer11:gameView->ActionSetControlledPlayerView(10);break;
	case cameraActionCameraFocusPlayer12:gameView->ActionSetControlledPlayerView(11);break;
		
	case cameraActionZoomOutLockCamera:
		m_cameraDirector->Zoom(deltaTime, 0.1f, false, 'o', 0.1f);
		break;
	case cameraActionZoomInLockCamera:
		m_cameraDirector->Zoom(deltaTime, 0.1f, false, 'i', 0.1f);
		break;
	case cameraActionMMBZoom:

		switch (m_cameraDirector->GetUsingCamera())
		{
		case usingLockCamera:
		case usingThirdPersonCamera://intentionally use this behavior for 3rd person as well.
			if (sm_gameInputController->GetZDelta() > 0)
			{
				m_cameraDirector->Zoom(deltaTime, 2.0f, true, 'i', 0.01/deltaTime);
			}
			else
			{
				if (sm_gameInputController->GetZDelta() < 0)
				{
					m_cameraDirector->Zoom(deltaTime, 2.0f, true, 'o', 0.01/deltaTime);
				}
			}
			break;
		}

		break;
	case cameraActionToggleFreeCamera:
		m_cameraDirector->ActionToggleFreeCamera(gameState->GetControlledActor());//not a game feature
		
		break;//not a game feature

	case cameraActionFreeLeft: m_cameraDirector->FlyLeft(deltaTime); break;
	case cameraActionFreeRight: m_cameraDirector->FlyRight(deltaTime); break;
	case cameraActionFreeForward: m_cameraDirector->FlyForward(deltaTime); break;
	case cameraActionFreeBackward: m_cameraDirector->FlyBackward(deltaTime); break;
	case cameraActionFreeUp: m_cameraDirector->FlyUp(deltaTime); break;
	case cameraActionFreeDown: m_cameraDirector->FlyDown(deltaTime); break;
	case cameraActionFreeAccel: m_cameraDirector->AddZDelta(g_inputControl.GetZDelta(), deltaTime); break;
	case cameraActionFreePitchYaw:



		if (m_cameraDirector->IsUsingFly()
			|| m_cameraDirector->GetUsingCamera() == usingThirdPersonCamera )
		{

			if (m_cameraDirector->GetUsingCamera() == usingThirdPersonCamera)
			{

				m_cameraDirector->PitchImpulse(g_inputControl.GetYDelta() * deltaTime);
				m_cameraDirector->YawImpulse(g_inputControl.GetXDelta() * deltaTime);
			}
			else
			{
				m_cameraDirector->GetPointerToCurrentCamera()->Yaw(
					g_inputControl.GetXDelta() * 0.0022f);
				m_cameraDirector->GetPointerToCurrentCamera()->Pitch(
					g_inputControl.GetYDelta() * 0.0022f);
			}

			RECT r;
			GetWindowRect(g_hwnd, &r);
			SetCursorPos(r.left + 0.5f * (float)g_clientSizeRect->right,r.top + 0.5f * (float)g_clientSizeRect->bottom);
		}
		break;
	}	
}

void CameraInputSet::SetCameraDirector(CameraDirector * cameraDirector)
{
	m_cameraDirector = cameraDirector;
}

void CameraInputSet::SpamAction(int action, float deltaTime)
{

}