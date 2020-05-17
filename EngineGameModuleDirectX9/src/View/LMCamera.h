#if !defined(LMCAMERA_H)
#define LMCAMERA_H

#include <string>
using std::string;

#include <d3dx9math.h>
//#include <d3d9.h>


enum projectionType
{
	projection3d,
	projectionOrthographic,
	projectionCount
};

enum cameraLockTypes
{
	cameraLockStatic,
	cameraLockLookAt,
	cameraLockNone,
	cameralockCount
};

class LMCamera
{

	//ProjectionType To Orthographic

private:
	D3DXMATRIX  m_view;
	D3DXMATRIX  m_projection;
	D3DXVECTOR3 m_right;
	D3DXVECTOR3 m_up;
	D3DXVECTOR3 m_look;
	D3DXVECTOR3 m_position;
	D3DXVECTOR3 m_lookAt;
	D3DXVECTOR3 m_velocity;
	float       m_yaw;
	float       m_pitch;
	float       m_maxPitch;
	float       m_maxVelocity;
	float       m_fov;
	float       m_aspect;
	float       m_nearPlane;
	float       m_farPlane;
	BOOL        m_invertY;
	BOOL        m_enableYMovement;

	D3DXVECTOR3 m_cameraLockVector; //init
	cameraLockTypes m_cameraLockType;
	projectionType m_projectionType;
	float m_playerZoomMin;
	float m_playerZoomLevel;
	float m_playerZoomMax;
	float m_zoomVelocity;
	//moving from player to half way between player and moving object


public:
	LMCamera::LMCamera();
	LMCamera(projectionType projtype, cameraLockTypes locktype, float fov);
	virtual ~LMCamera();
	void Update();
	void Update2();

	void Init(float v, float width, float height, D3DXVECTOR3 * position, D3DXVECTOR3 * lookat);
	void OrthoInit(float v, float width, float height, D3DXVECTOR3 * position, D3DXVECTOR3 * lookat);
	void PerspectiveInit(float v, float width, float height, D3DXVECTOR3 * position, D3DXVECTOR3 * lookat);

	void CreateProjectionMatrix(float fov, float aspect, float nearPlane, float farPlane);
	void CreateProjectionMatrixOrtho(float width, float height, float nearPlane, float farPlane);

	//unlocked camera functions
	void MoveForward(float units);
	void Strafe(float units);
	void MoveUp(float units);
	void Yaw(float radians);
	void Pitch(float radians);
	void Roll(float radians);

	//mutators
	void SetMaxVelocity(float maxVelocity) { m_maxVelocity = maxVelocity; }
	void SetInvertY(BOOL invert)           { m_invertY = invert; }
	void SetMaxPitch(float maxPitch)       { m_maxPitch = maxPitch; }
	void SetPosition(D3DXVECTOR3* pPosition);
	void SetLookAt(D3DXVECTOR3* pLookAt);
	void SetFOV(float fov)            { CreateProjectionMatrix(fov, m_aspect, m_nearPlane, m_farPlane); }
	void SetAspectRatio(float aspect) { CreateProjectionMatrix(m_fov, aspect, m_nearPlane, m_farPlane); }
	void SetNearPlane(float plane)    { CreateProjectionMatrix(m_fov, m_aspect, plane, m_farPlane); }
	void SetFarPlane(float plane)     { CreateProjectionMatrix(m_fov, m_aspect, m_nearPlane, plane); }
	void SetZoomLevel(float zoom) 	  { m_playerZoomLevel = zoom; }
	void AdjustZoomLevel(float zoomChange);
	void SetZoomMinMix(float min, float max);

	//accessors
	D3DXMATRIX* GetViewMatrix()        { return &m_view; }
	D3DXMATRIX* GetProjectionMatrix()  { return &m_projection; }
	D3DXVECTOR3* GetPosition()         { return &m_position; }
	D3DXVECTOR3* GetLookAt()           { return &m_lookAt; }
	D3DXVECTOR3* GetLook()			   { return &m_look; }
	float GetFOV()                     { return m_fov; }
	float GetAspectRatio()             { return m_aspect; }
	float GetNearPlane()               { return m_nearPlane; }
	float GetFarPlane()                { return m_farPlane; }
	float GetMaxVelocity()             { return m_maxVelocity; }
	BOOL  GetInvertY()                 { return m_invertY; }
	float GetPitch()                   { return m_pitch; }
	float GetYaw()                     { return m_yaw; }
	float GetMaxPitch()                { return m_maxPitch; }
	float GetZoomLevel()			   { return m_playerZoomLevel; }
};

#endif
