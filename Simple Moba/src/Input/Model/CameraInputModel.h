#if !defined(CAMERAINPUTMODEL_H)
#define CAMERAINPUTMODEL_H


enum CameraActions
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
	cameraActionFreePitchYaw,

	cameraActionCount
};


#include "../../../../EngineGameModuleDirectX9/src/Input/InputModel.h"


class CameraInputModel : public InputModel
{
public:
	CameraInputModel();
	bool Init(string path);
	~CameraInputModel();
};

#endif;