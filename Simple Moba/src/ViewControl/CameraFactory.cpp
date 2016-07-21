#include "CameraFactory.h"

CameraFactory::CameraFactory(){}
CameraFactory::~CameraFactory(){}

LMCamera CameraFactory::ConstructMenuUICamera(projectionType projtype, cameraLockTypes locktype)
{
	return LMCamera(projtype, locktype, D3DX_PI / 12.0f);
}

LMCamera CameraFactory::ConstructGameUICamera(projectionType projtype, cameraLockTypes locktype)
{
	return LMCamera(projtype, locktype, D3DX_PI / 12.0f);
}

LMCamera CameraFactory::ConstructGameLockCamera(projectionType projtype, cameraLockTypes locktype)
{
	return LMCamera(projtype, locktype, D3DX_PI / 12.0f);
}

LMCamera CameraFactory::ConstructGameFreeCamera(projectionType projtype, cameraLockTypes locktype)
{
	return LMCamera(projtype, locktype, D3DX_PI / 4.0f);
}

LMCamera CameraFactory::ConstructGameThirdPersonCamera(projectionType projtype, cameraLockTypes locktype)
{
	return LMCamera(projtype, locktype, D3DX_PI / 4.0f);
}


