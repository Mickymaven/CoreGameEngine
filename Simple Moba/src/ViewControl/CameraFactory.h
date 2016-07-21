#if !defined(CAMERAFACTORY_H)
#define CAMERAFACTORY_H

#include "../../../EngineGameModuleDirectX9/src/View/LMCamera.h"
#include "../../../EngineGameModuleDirectX9/src/Application/Globals.h"

class CameraFactory
{
private:
public:
	CameraFactory();
	virtual ~CameraFactory();

	LMCamera ConstructMenuUICamera(projectionType projtype, cameraLockTypes locktype);
	LMCamera ConstructGameUICamera(projectionType projtype, cameraLockTypes locktype);
	LMCamera ConstructGameLockCamera(projectionType projtype, cameraLockTypes locktype);
	LMCamera ConstructGameFreeCamera(projectionType projtype, cameraLockTypes locktype);
	LMCamera ConstructGameThirdPersonCamera(projectionType projtype, cameraLockTypes locktype);

};

#endif
