#include "LMCamera.h"


LMCamera::LMCamera()
{

}

LMCamera::LMCamera(projectionType projtype, cameraLockTypes locktype, float fov)
{
	m_up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	m_fov = fov;

	m_cameraLockVector = D3DXVECTOR3(0.0f, 0.83205f, -0.5547f);
	m_playerZoomLevel = 60.0f;
	m_zoomVelocity = 50.0f;
	m_playerZoomMin = 10.0f;
	m_playerZoomMax = 350.0f;
	m_cameraLockType = locktype;
	m_projectionType = projtype;

	m_maxPitch = D3DXToRadian(89.0f);
	m_maxVelocity = 1.0f;
	m_invertY = FALSE;
	m_enableYMovement = TRUE;


}

LMCamera::~LMCamera()
{

}

void LMCamera::Init(float v, float width, float height, D3DXVECTOR3 * position, D3DXVECTOR3 * lookat)
{
	//once constructing all the cameras use this to init based on client area vars.
	//Can potentionally be reused to reinit (on client size change).

	m_maxVelocity = v;
	m_position = *position; //copy

	SetLookAt(lookat);
	//	m_lookAt = *lookat; //copy
	
	if (height > 0.0f) m_aspect = width / height;
	else m_aspect = 1.0f;

	m_velocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	switch (m_projectionType)
	{
	case projectionOrthographic:OrthoInit(v, width, height, position, lookat); break;
	case projection3d:PerspectiveInit(v, width, height, position, lookat); break;
	}

	Update();//should we
}

void LMCamera::OrthoInit(float v, float width, float height, D3DXVECTOR3 * position, D3DXVECTOR3 * lookat)//use externally
{
	D3DXMatrixLookAtLH(&m_view, position, lookat, &m_up);

	CreateProjectionMatrixOrtho(width, height, 0.0f, 1.1f);
}

void LMCamera::PerspectiveInit(float v, float width, float height, D3DXVECTOR3 * position, D3DXVECTOR3 * lookat)
{
	CreateProjectionMatrix(m_fov, m_aspect, 0.1f, 4000.0f); // is D3DXMatrixPerspectiveFovLH
}

void LMCamera::Update()
{
	m_up.x = 0.0f;
	m_up.y = 1.0f;
	m_up.z = 0.0f;

	if (m_projectionType == projection3d)
	{
		if (D3DXVec3Length(&m_velocity) > m_maxVelocity)
		{
			m_velocity = *(D3DXVec3Normalize(&m_velocity, &m_velocity)) * m_maxVelocity;
		}
		m_position += m_velocity;
		m_lookAt = m_position + m_look;

		if (abs(m_velocity.x) + abs(m_velocity.y) + abs(m_velocity.z) < 1.0f)
		{
			m_velocity.x = 0.0f;
			m_velocity.y = 0.0f;
			m_velocity.z = 0.0f;
		}
		else
		{
			m_velocity.x *= 0.5f;
			m_velocity.y *= 0.5f;
			m_velocity.z *= 0.5f;
		}

		D3DXMatrixLookAtLH(&m_view, &m_position, &m_lookAt, &m_up);

		m_right.x = m_view._11;
		m_right.y = m_view._21;
		m_right.z = m_view._31;
		m_up.x = m_view._12;
		m_up.y = m_view._22;
		m_up.z = m_view._32;
		m_look.x = m_view._13;
		m_look.y = m_view._23;
		m_look.z = m_view._33;

		float lookLengthOnXZ = sqrtf(m_look.z * m_look.z + m_look.x * m_look.x);
		m_pitch = atan2f(m_look.y, lookLengthOnXZ);
		m_yaw = atan2f(m_look.x, m_look.z);


	}
	else if (m_projectionType == projectionOrthographic)
	{

	}
}

void LMCamera::Update2()
{

	m_up.x = 0.0f;
	m_up.y = 1.0f;
	m_up.z = 0.0f;

	m_lookAt = m_position + m_look;

	//m_lookAt = m_position + m_look;

	D3DXMatrixLookAtLH(&m_view, &m_position, &m_lookAt, &m_up);

	m_right.x = m_view._11;
	m_right.y = m_view._21;
	m_right.z = m_view._31;
	m_up.x = m_view._12;
	m_up.y = m_view._22;
	m_up.z = m_view._32;
	m_look.x = m_view._13;
	m_look.y = m_view._23;
	m_look.z = m_view._33;
}

void LMCamera::CreateProjectionMatrix(float fov, float aspect, float nearPlane, float farPlane)
{

	//only for non Orthographic
	m_fov = fov;
	m_aspect = aspect;
	m_nearPlane = nearPlane;
	m_farPlane = farPlane;
	D3DXMatrixPerspectiveFovLH(&m_projection, m_fov, m_aspect, m_nearPlane, m_farPlane);
}

void LMCamera::CreateProjectionMatrixOrtho(float width, float height,float nearPlane,float farPlane)
{
	m_nearPlane = nearPlane;
	m_farPlane = farPlane;

	D3DXMatrixOrthoLH(&m_projection, width, height, 0.0f, 1.1f);
}


void LMCamera::MoveForward(float units)
{
	if (m_enableYMovement)
	{
		m_velocity += m_look * units;
	}
	else
	{
		D3DXVECTOR3 moveVector(m_look.x, 0.0f, m_look.z);
		D3DXVec3Normalize(&moveVector, &moveVector);
		moveVector *= units;
		m_velocity += moveVector;
	}
}

void LMCamera::Strafe(float units)
{
	m_velocity += m_right * units;
}

void LMCamera::MoveUp(float units)
{
	if (m_enableYMovement)
	{
		m_velocity.y += units;
	}
}

void LMCamera::Yaw(float radians)
{
	if (radians == 0.0f)
	{
		return;
	}
	D3DXMATRIX rotation;
	D3DXMatrixRotationAxis(&rotation, &m_up, radians);
	D3DXVec3TransformNormal(&m_right, &m_right, &rotation);
	D3DXVec3TransformNormal(&m_look, &m_look, &rotation);
}

void LMCamera::Pitch(float radians)
{
	if (radians == 0.0f)
	{
		return;
	}

	radians = (m_invertY) ? -radians : radians;
	m_pitch -= radians;
	if (m_pitch > m_maxPitch)
	{
		radians += m_pitch - m_maxPitch;
	}
	else if (m_pitch < -m_maxPitch)
	{
		radians += m_pitch + m_maxPitch;
	}

	D3DXMATRIX rotation;
	D3DXMatrixRotationAxis(&rotation, &m_right, radians);
	D3DXVec3TransformNormal(&m_up, &m_up, &rotation);
	D3DXVec3TransformNormal(&m_look, &m_look, &rotation);

}

void LMCamera::Roll(float radians)
{
	if (radians == 0.0f)
	{
		return;
	}
	D3DXMATRIX rotation;
	D3DXMatrixRotationAxis(&rotation, &m_look, radians);
	D3DXVec3TransformNormal(&m_right, &m_right, &rotation);
	D3DXVec3TransformNormal(&m_up, &m_up, &rotation);
}

void LMCamera::SetPosition(D3DXVECTOR3* pPosition)
{
	m_position = *pPosition;
}

void LMCamera::SetLookAt(D3DXVECTOR3* pLookAt)
{
	m_lookAt = *pLookAt;

	if (m_cameraLockType == cameraLockLookAt)
	{

		m_position.x = m_lookAt.x;
		m_position.y = m_lookAt.y + (m_cameraLockVector.y * m_playerZoomLevel) + 2.1f;
		m_position.z = m_lookAt.z + (m_cameraLockVector.z * m_playerZoomLevel);

	}

	D3DXVec3Normalize(&m_look, &(m_lookAt - m_position));
}

void LMCamera::AdjustZoomLevel(float zoomChange)

{//I AM ADDING + OR - deltatime as zoom change on locked camera in game
	m_playerZoomLevel += zoomChange * m_zoomVelocity;

	if (m_playerZoomLevel < m_playerZoomMin) m_playerZoomLevel = m_playerZoomMin;
	else if (m_playerZoomLevel > m_playerZoomMax) m_playerZoomLevel = m_playerZoomMax;
}

void LMCamera::SetZoomMinMix(float min, float max)
{
	m_playerZoomMin = min;
	m_playerZoomMax = max;
}