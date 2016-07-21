#include "CameraInputModel.h"

CameraInputModel::CameraInputModel()
{}

bool CameraInputModel::Init(string path)
{

	m_path = "Resources/Settings/CameraInput.keys";

	m_keybinds.resize(cameraActionCount);

	m_keybinds[cameraActionCameraPanModifier] = MO_MIDDLE_BUTTON;
	m_keybinds[cameraActionToggleCameraLock] = DIK_Y;
	m_keybinds[cameraActionCentreCamera] = DIK_SPACE;

	m_keybinds[cameraActionCameraFocusPlayer1] = DIK_F1;
	m_keybinds[cameraActionCameraFocusPlayer2] = DIK_F2;
	m_keybinds[cameraActionCameraFocusPlayer3] = DIK_F3;
	m_keybinds[cameraActionCameraFocusPlayer4] = DIK_F4;
	m_keybinds[cameraActionCameraFocusPlayer5] = DIK_F5;
	m_keybinds[cameraActionCameraFocusPlayer6] = DIK_F6;
	m_keybinds[cameraActionCameraFocusPlayer7] = DIK_F7;
	m_keybinds[cameraActionCameraFocusPlayer8] = DIK_F8;
	m_keybinds[cameraActionCameraFocusPlayer9] = DIK_F9;
	m_keybinds[cameraActionCameraFocusPlayer10] = DIK_F10;
	m_keybinds[cameraActionCameraFocusPlayer11] = DIK_F11;
	m_keybinds[cameraActionCameraFocusPlayer12] = DIK_F12;

	m_keybinds[cameraActionZoomOutLockCamera] = DIK_MINUS;
	m_keybinds[cameraActionZoomInLockCamera] = DIK_EQUALS;
	m_keybinds[cameraActionMMBZoom] = MO_ZDELTA;

	m_keybinds[cameraActionToggleFreeCamera] = DIK_X;//DIK_BACKSLASH
	m_keybinds[cameraActionFreeLeft] = DIK_COMMA;
	m_keybinds[cameraActionFreeRight] = DIK_SLASH;
	m_keybinds[cameraActionFreeForward] = DIK_L;
	m_keybinds[cameraActionFreeBackward] = DIK_PERIOD;
	m_keybinds[cameraActionFreeUp] = DIK_K;
	m_keybinds[cameraActionFreeDown] = DIK_M;
	m_keybinds[cameraActionFreeAccel] = MO_ZDELTA;
	m_keybinds[cameraActionFreePitchYaw] = MO_MIDDLE_BUTTON;


	m_spamFlags.resize(cameraActionCount, false);

	m_spamFlags[cameraActionCentreCamera] = true;
	m_spamFlags[cameraActionZoomOutLockCamera] = true;
	m_spamFlags[cameraActionZoomInLockCamera] = true;
	m_spamFlags[cameraActionCameraPanModifier] = true;

	m_spamFlags[cameraActionFreeLeft] = true;
	m_spamFlags[cameraActionFreeRight] = true;
	m_spamFlags[cameraActionFreeForward] = true;
	m_spamFlags[cameraActionFreeBackward] = true;
	m_spamFlags[cameraActionFreeUp] = true;
	m_spamFlags[cameraActionFreeDown] = true;
	m_spamFlags[cameraActionFreeAccel] = true;
	m_spamFlags[cameraActionFreePitchYaw] = true;

	vector<int> full
	{
		cameraActionCameraPanModifier,
		cameraActionToggleCameraLock,
		cameraActionCentreCamera,

		cameraActionCameraFocusPlayer1,
		cameraActionCameraFocusPlayer2,
		cameraActionCameraFocusPlayer3,
		cameraActionCameraFocusPlayer4,
		cameraActionCameraFocusPlayer5,
		cameraActionCameraFocusPlayer6,
		cameraActionCameraFocusPlayer7,
		cameraActionCameraFocusPlayer8,
		cameraActionCameraFocusPlayer9,
		cameraActionCameraFocusPlayer10,
		cameraActionCameraFocusPlayer11,
		cameraActionCameraFocusPlayer12,

		cameraActionZoomOutLockCamera,
		cameraActionZoomInLockCamera,
		cameraActionMMBZoom,

		cameraActionToggleFreeCamera,//not a game feature
		cameraActionFreeLeft,
		cameraActionFreeRight,
		cameraActionFreeForward,
		cameraActionFreeBackward,
		cameraActionFreeUp,
		cameraActionFreeDown,
		cameraActionFreeAccel,
		cameraActionFreePitchYaw
	};

	m_actionsforState.resize(1);

	m_actionsforState.at(0) = full;

	return true;
}

CameraInputModel::~CameraInputModel() {}