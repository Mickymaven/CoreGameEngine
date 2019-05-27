#if !defined(CAMERADIRECTOR_H)
#define CAMERADIRECTOR_H

#include "../../../EngineGameModel/src/Maths/LMVector2.h"
#include "../../../EngineGameModuleDirectX9/src/View/LMCamera.h"
#include "../../../EngineMoba/src/Actors/Actor.h"
#include "../../../EngineMoba/src/Actors/PlayerCharacterController.h"
#include "../../../CoreGame/src/Gamestate/StandardMatch5v5State.h"

#include "../GameplayView/PlayerCharacterView.h"

#include "../../../EngineGameModuleDirectX9/src/Application/GlobalsDX9.h"//todo bad?

#include "CameraFactory.h"

enum UsingGameCamera
{
	usingFlyCamera,
	usingLockCamera,
	usingInterfaceCamera,
	usingThirdPersonCamera,
	usingGameCameraCount
};

class CameraDirector
{
private:
	CameraFactory m_cameraFactory;

	MobaState * gameState;

	bool m_isLockCameraLocked;

	UsingGameCamera m_cameraSelectionState;//why is there no cuurent camera pointer :/ silly me
	UsingGameCamera m_currentGameCamera;

	



	LMCamera m_interfaceCamera;
		D3DXVECTOR3 m_interfacePosition;
		D3DXVECTOR3 m_interfaceLookAt;

	LMCamera m_lockedCamera;
		D3DXVECTOR3 m_lockedPosition;
		D3DXVECTOR3 m_lockedLookAt;

	LMCamera m_flyCamera;
		D3DXVECTOR3 m_flyPosition;
		D3DXVECTOR3 m_flyLookAt;
	float m_flyVelocity;

	LMCamera m_thirdPerson;
		D3DXVECTOR3 m_thirdPosition;
		D3DXVECTOR3 m_thirdLookAt;
	


	float pitchVelocity;
	float pitchVelocityThisUpdate;

	float yawVelocity;
	float yawVelocityThisUpdate;






	//D3DXVECTOR3 m_lockedPos = D3DXVECTOR3(-50.0f, 50.0f, -50.0f); //



	D3DXVECTOR3 m_unlockLookAt;

	LMVector2 m_panOrigin;
	LMVector2 m_panLast;
	LMVector2 m_panCurrent;
	LMVector2 m_panDisplacment;

	bool m_centreCameraAfterPlayerUpdate;

	vector<PlayerCharacterController *> * m_allPlayers;
	vector<PlayerCharacterView *> * m_allPlayerViews;

	//3rd person camera behavior;
	LMVector3 * playerPos;
	D3DXVECTOR3 lookDisp;
	D3DXVECTOR3 disp;

	float m_thirdPersonZoom;
	D3DXVECTOR3 m_thirdPersonLookAt;

public:
	UsingGameCamera m_gameCameraThisUpdate;

	CameraDirector();
	~CameraDirector();

	bool Init(MobaState * gameStateIn, vector<PlayerCharacterView *> * playerViews);


	void Update(float deltaTime, Actor *  actorWithFocus);

	void ActionToggleCameraLock(Actor *  actorWithFocus);
	void ActionCentreCamera(Actor *  actorWithFocus);
	void ActionToggleFreeCamera(Actor *  actorWithFocus);

	void ApplyLockedCameraMovement(LMVector2 * panDisplacment);
	void ApplyLockedCameraMovement();

	UsingGameCamera GetSelectedCameraState() { return m_cameraSelectionState; }


	LMCamera * GetUsingCamera(UsingGameCamera camera);


	void SetIsCameraLocked(bool isLocked) { m_isLockCameraLocked = isLocked; }
	void SetUsingCamera(UsingGameCamera camera);

	bool GetIsCameraLocked() { return m_isLockCameraLocked; }
	UsingGameCamera GetUsingCamera() { return m_cameraSelectionState; };


	
	LMCamera * GetPointerToCurrentCamera();

	void SetGameView();
	void SetGameProjection();

	void Zoom(float deltaTime, const char dir, float multi);

	void StoreLookAt(Actor *  actorWithFocus);

	void GetStateAsString(int i);

	void SwitchToCurrentGameCamera();

	void InterfaceProjection();
	void InterfaceView();

	bool IsUsingFly();
	void FlyUp(float deltaTime);
	void FlyDown(float deltaTime);
	void FlyLeft(float deltaTime);
	void FlyRight(float deltaTime);
	void FlyForward(float deltaTime);
	void FlyBackward(float deltaTime);
	void AddZDelta(float deltaTime, float zDelta);
	void FlyPitchYaw(float deltaTime, float pitch, float yaw);

	void CameraPanBehavior(bool mouseDownLast);

	void ActionCameraFocusPlayer(unsigned int i);

	void CentreCameraAfterPlayerUpdate();
	void UpdateCameraStatesAfterPlayerMovement(Actor * playerCharacter);

	float * GetThirdPersonZoom();

	void SetOrthographic(LMCamera * cam);
	void SetProjection(LMCamera * cam);

	void PitchImpulse(float yDelta);
	void YawImpulse(float xDelta);
	void CentreThirdPersonCam(Actor * actor);


};

#endif
