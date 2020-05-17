#include "CameraDirector.h"

CameraDirector::CameraDirector()
{
	


}
CameraDirector::~CameraDirector()
{

}

bool CameraDirector::Init(MobaState * gameStateIn, vector<PlayerCharacterView *> * playerViews)
{


	pitchVelocity=0;
	pitchVelocityThisUpdate=0;

	yawVelocity=0;
	yawVelocityThisUpdate=0;

	vector<PlayerCharacterView *> * m_allPlayerViews = playerViews;

	gameState = gameStateIn;
	//vector<PlayerCharacterController* > * allPlayers
	
	//m_allPlayers = gameState->GetPCCs();

	m_isLockCameraLocked = false;
	m_cameraSelectionState = usingFlyCamera;
	m_currentGameCamera = usingFlyCamera;

	playerPos = NULL;

	disp = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	lookDisp = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_centreCameraAfterPlayerUpdate = false;
	

	m_flyVelocity = 100.0f;

	//just do this before we init just to be sure we have right aspect / view

	GetClientRect(g_hwnd, g_clientSizeRect);
	float w = (float)g_clientSizeRect->right;
	float h = (float)g_clientSizeRect->bottom;

	//Init as we dont want factory to care much about positions/look at. (in principle)

	m_interfacePosition = D3DXVECTOR3(0.5f * w, -1.0f, 0.5f * h - 0.0001f);
	m_interfaceLookAt = D3DXVECTOR3(0.5f * w, 0.0f, 0.5f * h);
	m_interfaceCamera = m_cameraFactory.ConstructGameFreeCamera(projectionOrthographic, cameraLockStatic);
	m_interfaceCamera.Init(0.0f,w,h, &m_interfacePosition, &m_interfaceLookAt);

	//game cameras (represented by enum)
	m_lockedPosition = D3DXVECTOR3(-50.0f, 50.0f, -50.0f);
	m_lockedLookAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_lockedCamera = m_cameraFactory.ConstructGameLockCamera(projection3d, cameraLockLookAt);
	m_lockedCamera.Init(200.0f,w,h, &m_lockedPosition, &m_lockedLookAt);

	m_unlockLookAt = D3DXVECTOR3(0.0f,0.0f,0.0f);


	m_flyPosition = D3DXVECTOR3(200, 500.0f, -100.0f);
	m_flyLookAt = D3DXVECTOR3(200.0f, 0.0f, 175.0f);
	m_flyCamera = m_cameraFactory.ConstructGameFreeCamera(projection3d, cameraLockNone);
	m_flyCamera.Init(300.0f, w, h, &m_flyPosition, &m_flyLookAt);


	m_thirdPosition = D3DXVECTOR3(200, 375.0f, 0.0f);
	m_thirdLookAt = D3DXVECTOR3(200.0f, 0.0f, 160.0f);
	m_thirdPerson = m_cameraFactory.ConstructGameThirdPersonCamera(projection3d, cameraLockNone);
	m_thirdPerson.Init(100.0f, w, h, &m_thirdPosition, &m_thirdLookAt);
	m_thirdPerson.SetZoomMinMix(1.7f, 100.0f);


	return true;
}

void CameraDirector::Update(float deltaTime, Actor *  actorWithFocus)
{
	switch (m_cameraSelectionState)
	{
	case usingFlyCamera:
		m_flyCamera.Update();
		//OutputDebugString("State Fly Camera \n");
		break;

	case usingLockCamera:
		//OutputDebugString("State Lock Camera \n");
		if (m_isLockCameraLocked) ActionCentreCamera(actorWithFocus);
		break;


	case usingThirdPersonCamera:
		//Todo is adding zoom to third person for fun.. maybe smooth 3rd person?
		//wont make 3rd person controller but might move it later

		// PITCH YAW STUFF //////////////////////////////
		if (m_thirdPerson.GetPosition()->y < -0.2f && pitchVelocityThisUpdate < 0.05f) pitchVelocityThisUpdate += 0.0025f;
		if (m_thirdPerson.GetPosition()->y > 0.9f*(m_thirdPerson.GetZoomLevel() + 2.1f) && pitchVelocityThisUpdate > -0.05f) pitchVelocityThisUpdate -= 0.0025f;

		//pitch / yaw
		yawVelocity += yawVelocityThisUpdate * 9.0f * deltaTime;
		pitchVelocity += pitchVelocityThisUpdate * 9.0f * deltaTime;


		yawVelocity -= 6.0f*deltaTime*yawVelocity;
		pitchVelocity -= 6.0f*deltaTime*pitchVelocity;

		m_thirdPerson.Pitch(pitchVelocity);
		m_thirdPerson.Yaw(yawVelocity);

		yawVelocityThisUpdate = 0.0f;
		pitchVelocityThisUpdate = 0.0f;


		//POSITION LOOKAT STUFF ////////////////////////

		playerPos = actorWithFocus->GetPhysicsObject()->GetPosition();


		lookDisp = *m_thirdPerson.GetPosition() - *m_thirdPerson.GetLookAt();

		D3DXVec3Normalize(&lookDisp, &lookDisp);

		if (true)
		{
			m_thirdPersonLookAt.x = playerPos->x;
			m_thirdPersonLookAt.y = playerPos->y + 2.1f;
			m_thirdPersonLookAt.z = playerPos->z;
		}

		disp.x = m_thirdPersonLookAt.x + m_thirdPerson.GetZoomLevel() * lookDisp.x;
		disp.y = m_thirdPersonLookAt.y + m_thirdPerson.GetZoomLevel() * lookDisp.y;
		disp.z = m_thirdPersonLookAt.z + m_thirdPerson.GetZoomLevel() * lookDisp.z;

		m_thirdPerson.GetPosition()->x = disp.x;
		m_thirdPerson.GetPosition()->y = disp.y;//m_thirdPerson.GetPosition()->y = 3.1f;
		m_thirdPerson.GetPosition()->z = disp.z;


		m_thirdPerson.Update();   //m_thirdPerson.SetLookAt(&m_thirdPersonLookAt);
		m_thirdPerson.SetPosition(&disp);
		SetGameView();
		SetGameProjection();
		////////////////////////////////////////////////
		break;

	case usingInterfaceCamera:
		//m_interfaceCamera.Update();
		break;

	default:
		usingInterfaceCamera;
		MessageBox(NULL, "Bad active camera state in game controller update().", "error", MB_OK);
		break;
	}
}

void CameraDirector::ActionToggleCameraLock(Actor *  actorWithFocus)
{
	if (m_isLockCameraLocked)
	{
		StoreLookAt(actorWithFocus);
	}

	m_isLockCameraLocked = !m_isLockCameraLocked;

}

void CameraDirector::ActionCentreCamera(Actor *  actorWithFocus)
{
	if (m_cameraSelectionState == usingLockCamera)
	{
		//OutputDebugString("Centre Camera Function\n");

		m_lockedCamera.SetLookAt(
			(D3DXVECTOR3*)actorWithFocus->GetPhysicsObject()->GetPosition());
		m_lockedCamera.Update();

		SetGameView();
		SetGameProjection();

		StoreLookAt(actorWithFocus);
	}


}

void CameraDirector::ActionToggleFreeCamera(Actor *  actorWithFocus)
{
	if (m_cameraSelectionState == usingFlyCamera)
	{
		SetUsingCamera(usingLockCamera);
		ActionCentreCamera(actorWithFocus);
	}
	else if (m_cameraSelectionState == usingLockCamera)
	{
		CentreThirdPersonCam(gameState->GetControlledActor());

		SetUsingCamera(usingThirdPersonCamera);
	}
	else if (m_cameraSelectionState == usingThirdPersonCamera)
	{
		SetUsingCamera(usingFlyCamera);
	}
	else SetUsingCamera(usingFlyCamera);
}


void CameraDirector::ApplyLockedCameraMovement(LMVector2 * panDisplacment)
{
	if (m_cameraSelectionState == usingLockCamera)
	{
		m_unlockLookAt =
			D3DXVECTOR3(
			m_unlockLookAt.x + panDisplacment->x,
			0.0f,
			m_unlockLookAt.z + (panDisplacment->y*-1.0f)
			);

		m_lockedCamera.SetLookAt(&m_unlockLookAt);

		m_lockedCamera.Update();

		//SetGameView();
		//SetGameProjection();
	}
}

void CameraDirector::ApplyLockedCameraMovement()
{
	ApplyLockedCameraMovement(&m_panDisplacment);
}

LMCamera * CameraDirector::GetUsingCamera(UsingGameCamera camera)
{
	switch (camera)
	{
	case usingFlyCamera:
		return &m_flyCamera;
		break;
	case usingLockCamera:
		return & m_lockedCamera;
		break;
	case usingThirdPersonCamera:
		return & m_thirdPerson;
		break;
	case usingInterfaceCamera:
		return &m_interfaceCamera;
		break;
	}

	return NULL;
}

void CameraDirector::SetUsingCamera(UsingGameCamera camera)
{

	m_cameraSelectionState = camera;

	switch (camera)
	{
		case usingFlyCamera:
			m_currentGameCamera = usingFlyCamera;
			SetGameView();
			SetGameProjection();
			break;
		case usingLockCamera:
			m_currentGameCamera = usingLockCamera;
			SetGameView();
			SetGameProjection();
			break;
		case usingThirdPersonCamera:
			m_currentGameCamera = usingThirdPersonCamera;
			
			

			SetGameView();
			SetGameProjection();
			break;
		case usingInterfaceCamera:
			SetGameView();
			SetGameProjection();
			break;
		case usingGameCameraCount:
			return;

			break;
	}
}

void CameraDirector::SetGameView()
{
	switch (m_cameraSelectionState)
	{
	case usingFlyCamera:
		g_D3D_Device->SetTransform(D3DTS_VIEW, m_flyCamera.GetViewMatrix());
		break;
	case usingLockCamera:
		g_D3D_Device->SetTransform(D3DTS_VIEW, m_lockedCamera.GetViewMatrix());
		break;
	case usingThirdPersonCamera:
		g_D3D_Device->SetTransform(D3DTS_VIEW, m_thirdPerson.GetViewMatrix());
		break;
	case usingInterfaceCamera:
		g_D3D_Device->SetTransform(D3DTS_VIEW, m_interfaceCamera.GetViewMatrix());
		//InterfaceView();


		break;
	default:
		MessageBox(NULL, "Bad active camera state in game controller setcamera().", "error", MB_OK);
		break;
	}
}

void CameraDirector::SetGameProjection()
{
	switch (m_cameraSelectionState)
	{
	case usingFlyCamera:SetProjection(&m_flyCamera); break;
	case usingLockCamera: SetProjection(&m_lockedCamera); break;
	case usingThirdPersonCamera: SetProjection(&m_thirdPerson); break;
	case usingInterfaceCamera: SetProjection(&m_interfaceCamera); break;
	default:
		MessageBox(NULL, "Bad active camera state in game controller setperspective().", "error", MB_OK);
		break;
	}
}

LMCamera * CameraDirector::GetPointerToCurrentCamera()
{
	return GetUsingCamera(m_cameraSelectionState);
}

void CameraDirector::Zoom(float deltaTime, float factor, bool useFactor, const char dir, float multi)
{
	float factorUsed;

	if (useFactor) factorUsed = factor;
	else factorUsed = 0.01f;


	if (m_cameraSelectionState == usingLockCamera)
	{
		switch (dir)
		{
		case 'i':m_lockedCamera.AdjustZoomLevel(-1 * factorUsed * multi); break;//in
		case 'o':m_lockedCamera.AdjustZoomLevel(1 * factorUsed * multi); break;//out	
		default: break;
		}

		m_lockedCamera.SetLookAt(&m_unlockLookAt);
		m_lockedCamera.Update();
	}
	else if (m_cameraSelectionState == usingThirdPersonCamera)
	{
		switch (dir)
		{
		case 'i': m_thirdPerson.AdjustZoomLevel(-1 * factorUsed * multi);break;//in
		case 'o':m_thirdPerson.AdjustZoomLevel(1 * factorUsed * multi); break;//out
		default:break;
		}

		//m_thirdPerson.SetLookAt((D3DXVECTOR3*)playerPos);
		//m_thirdPerson.Update();
	}
	else if (m_cameraSelectionState == usingFlyCamera)
	{
		//CHANGE FOV?
	}
	SetGameView();
	SetGameProjection();

}

void CameraDirector::StoreLookAt(Actor *  actorWithFocus)
{
	m_unlockLookAt =
		D3DXVECTOR3(actorWithFocus->GetPhysicsObject()->GetPosition()->x,
			actorWithFocus->GetPhysicsObject()->GetPosition()->y,
			actorWithFocus->GetPhysicsObject()->GetPosition()->z);
}


void CameraDirector::GetStateAsString(int i)
{
	UsingGameCamera state = m_cameraSelectionState;

	switch (state)
	{
	case usingFlyCamera: return OutputDebugString("Fly Camera");
		break;
	case usingLockCamera: return OutputDebugString("Lock Camera");
		break;
	case usingInterfaceCamera: return OutputDebugString("Interface Camera");
		break;
	case usingThirdPersonCamera: return OutputDebugString("Third Person Camera");
		break;
	}
}

void CameraDirector::SwitchToCurrentGameCamera()
{
	SetUsingCamera(m_currentGameCamera);
}

void CameraDirector::InterfaceProjection()
{

	GetClientRect(g_hwnd, g_clientSizeRect);
	//proj
	D3DXMATRIX m_orthographicmatrix;
	D3DXMatrixOrthoLH(&m_orthographicmatrix, (float)g_clientSizeRect->right, (float)g_clientSizeRect->bottom, 0.0f, 1.1f);
	g_D3D_Device->SetTransform(D3DTS_PROJECTION, &m_orthographicmatrix);




}

void CameraDirector::InterfaceView()
{
	//view
	D3DXMATRIX m_view2dmatrix;
	D3DXVECTOR3 oposition = D3DXVECTOR3(0.5f * (float)g_clientSizeRect->right, -1.0f, 0.5f * (float)g_clientSizeRect->bottom - 0.0001f);
	D3DXVECTOR3 olookat = D3DXVECTOR3(0.5f * (float)g_clientSizeRect->right, 0.0f, 0.5f * (float)g_clientSizeRect->bottom);
	D3DXVECTOR3 oup = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	D3DXMatrixLookAtLH(&m_view2dmatrix, &oposition, &olookat, &oup);

	g_D3D_Device->SetTransform(D3DTS_VIEW, &m_view2dmatrix);

}

bool CameraDirector::IsUsingFly()
{
	if (m_currentGameCamera == usingFlyCamera) return true;
	return false;
}
void CameraDirector::FlyUp(float deltaTime)
{
	if (IsUsingFly()) m_flyCamera.MoveUp(deltaTime*m_flyVelocity);
}
void CameraDirector::FlyDown(float deltaTime)
{
	if (IsUsingFly()) m_flyCamera.MoveUp(deltaTime*-m_flyVelocity);
}
void CameraDirector::FlyLeft(float deltaTime)
{
	if (IsUsingFly()) m_flyCamera.Strafe(deltaTime*-m_flyVelocity);
}
void CameraDirector::FlyRight(float deltaTime)
{
	if (IsUsingFly())m_flyCamera.Strafe(deltaTime*m_flyVelocity);
}
void CameraDirector::FlyForward(float deltaTime)
{
	if (IsUsingFly()) m_flyCamera.MoveForward(deltaTime*m_flyVelocity);
}
void CameraDirector::FlyBackward(float deltaTime)
{
	if (IsUsingFly()) m_flyCamera.MoveForward(deltaTime*-m_flyVelocity);
}

void CameraDirector::AddZDelta(float deltaTime, float zDelta)
{
	if (IsUsingFly()) m_flyVelocity += zDelta * deltaTime;
	
	//limit
	if (m_flyVelocity < 5.0f) m_flyVelocity = 5.0f;
	else if (m_flyVelocity > 175.0f) m_flyVelocity = 175.0f;
}


void CameraDirector::FlyPitchYaw(float deltaTime, float pitch, float yaw)
{
	if (IsUsingFly())
	{
		m_flyCamera.Yaw(yaw *0.1f* 0.0167f);
		m_flyCamera.Pitch(pitch *0.1f* 0.0167f);
	}
}



void CameraDirector::CameraPanBehavior(bool mouseDownLast, float deltaTime)
{

	//if down on last update
	//if current mouse coords in client area
	//store as new current positions
	//(we will be left with last valid position otherwise)

	//calculate displacement of mouse coordinate position from orgin

	//make a change in camera lookat based on displacement vector


	//if not down on last update
	//if mouse in valid position in client
	//set new origin from current mouse coordinates
	//set current coordinates to be same as origin (to start of with)



	if (mouseDownLast)
	{

		m_panLast.x = m_panCurrent.x;
		m_panLast.y = m_panCurrent.y;

		if (g_mouseClientPosition.x > g_clientSizeRect->left)
		{
			if (g_mouseClientPosition.x < g_clientSizeRect->right)
			{
				if (g_mouseClientPosition.y > g_clientSizeRect->top)
				{
					if (g_mouseClientPosition.y < g_clientSizeRect->bottom)
					{
						m_panCurrent.x = (float)g_mouseClientPosition.x;
						m_panCurrent.y = (float)g_mouseClientPosition.y;
					}
				}
			}
		}

		m_panDisplacment.x = 0.1f * deltaTime * (m_panCurrent.x - m_panOrigin.x);
		m_panDisplacment.y = 0.1f *  deltaTime *  (m_panCurrent.y - m_panOrigin.y);


		ApplyLockedCameraMovement(&m_panDisplacment);

	}

	else //no panning key down last time, init new panning
	{

		if (g_mouseClientPosition.x > g_clientSizeRect->left)
		{
			if (g_mouseClientPosition.x < g_clientSizeRect->right)
			{
				if (g_mouseClientPosition.y > g_clientSizeRect->top)
				{
					if (g_mouseClientPosition.y < g_clientSizeRect->bottom)
					{
						m_panOrigin.x = (float)g_mouseClientPosition.x;
						m_panOrigin.y = (float)g_mouseClientPosition.y;

						m_panCurrent.x = (float)g_mouseClientPosition.x;
						m_panCurrent.y = (float)g_mouseClientPosition.y;
					}
				}
			}
		}
	}
}

void CameraDirector::ActionCameraFocusPlayer(unsigned int i)
{





}

void CameraDirector::CentreCameraAfterPlayerUpdate()
{
	m_centreCameraAfterPlayerUpdate = true;
}

void CameraDirector::UpdateCameraStatesAfterPlayerMovement(Actor * playerCharacter)
{
	if (m_centreCameraAfterPlayerUpdate)
	{
		ActionCentreCamera(playerCharacter);
		m_centreCameraAfterPlayerUpdate = false;
	}
}

//void SetAllPlayers(vector<ActorController*> * m_allPlayers);

float * CameraDirector::GetThirdPersonZoom() { return &m_thirdPersonZoom; }

void CameraDirector::SetOrthographic(LMCamera * cam)
{
	D3DXMATRIX m_orthographicmatrix;
	D3DXMatrixOrthoLH(&m_orthographicmatrix, (float)g_clientSizeRect->right, (float)g_clientSizeRect->bottom, 0.0f, 1.1f);
	g_D3D_Device->SetTransform(D3DTS_PROJECTION, &m_orthographicmatrix);
}

void CameraDirector::SetProjection(LMCamera * cam) //maybe move this to camera makes sense unless we want to keep teh device out of there.
{
	g_D3D_Device->SetTransform(D3DTS_PROJECTION, cam->GetProjectionMatrix());
}

void CameraDirector::PitchImpulse(float yDelta)
{
	pitchVelocityThisUpdate += yDelta;
}

void CameraDirector::YawImpulse(float xDelta)
{
	yawVelocityThisUpdate += xDelta;
}

void CameraDirector::CentreThirdPersonCam(Actor * actor)
{
	if (true)
	{
		playerPos = actor->GetPhysicsObject()->GetPosition();
		m_thirdPersonLookAt.x = playerPos->x;
		m_thirdPersonLookAt.y = playerPos->y + 2.1f;
		m_thirdPersonLookAt.z = playerPos->z;
	}



	//What happens when you press spacebar in third person

	//pan the camera around the actor to look to the facing direction.
	playerPos = actor->GetPhysicsObject()->GetPosition();

	// 1. Get Current Camera Rot
		//difference of lookat from camera
		//can we get this from LMCamera::m_look
		LMVector3 * look = (LMVector3*)m_thirdPerson.GetLook();
		float radiansLook = atan2(look->x, look->z);

	// 2. Get Rot in radians
		LMVector3 * rot = actor->GetPhysicsObject()->GetRotation();

		float roty = rot->y;
		float looky = radiansLook*2;

		char bufferX[1000];
		sprintf_s(bufferX, "\n Player rot y: %f \n", roty);
		OutputDebugString(bufferX);

		float cosplayerX = cos(playerPos->x);
		float sinplayerX = sin(playerPos->x);

		float cosplayerZ = cos(playerPos->z);
		float sinplayerZ = sin(playerPos->z);


		float radiansPlayer = atan2(playerPos->x, playerPos->z);

		char hay[63];
		
		

		

	//3. get difference
		//float yawTest = radiansPlayer + radiansLook;
		
		
		float yawTest = radiansLook - roty;
		sprintf_s(bufferX, "\n yaw test: %f \n", yawTest);
		OutputDebugString(bufferX);


	//4. choose which way to want to rotate
	//5. add yaw in that direction

	//just going to guess direction and see
		float yawImpulse = 0.001f * abs(0.5f*yawTest);
		float absYawUpdate = abs(yawVelocity);


		if (yawTest > 0.001f) 
		{
			if (yawTest > D3DX_PI && absYawUpdate < yawImpulse) YawImpulse(0.001f * abs(yawTest));//right (if >pi to anticlockwise)
			else YawImpulse(-0.001f * abs(yawTest));//left

		}
		else if (yawTest < -0.001f)
		{
			if (yawTest < -D3DX_PI && absYawUpdate < yawImpulse) YawImpulse(-0.001f * abs(yawTest));//left (if >pi to clockwise)
			else YawImpulse(0.001f * abs(yawTest));//right
		}

	//6. pitch to nearest if <30 || >60 (or something)
		if (m_thirdPerson.GetPosition()->y < 2.5f && pitchVelocityThisUpdate < 0.05f) PitchImpulse(0.0025f);
		if (m_thirdPerson.GetPosition()->y > 0.67f*(m_thirdPerson.GetZoomLevel() + 2.1f) && pitchVelocityThisUpdate > -0.05f) PitchImpulse(-0.0025f);
	
	//nb: with variable deltaTime, dont use for velocity
}
