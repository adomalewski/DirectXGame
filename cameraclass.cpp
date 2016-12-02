#include "cameraclass.h"

CameraClass::CameraClass(CameraType cameraType = FirstPerson)
	: m_cameraType(cameraType)
{
	m_up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_defaultLookAt = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_lookAt = m_defaultLookAt;

	D3DXVec3Cross(&m_defaultRight, &m_defaultLookAt, &m_up);
	m_right = m_defaultRight;

	m_camYaw = 0.0f;
	m_camPitch = 0.0f;
	m_camRoll = 0.0f;
}

CameraClass::CameraClass(const CameraClass& other)
{
}

CameraClass::~CameraClass()
{

}

void CameraClass::SetPosition(float x, float y, float z)
{
	m_position = D3DXVECTOR3(x, y, z);
}

void CameraClass::SetRotation(float yaw, float pitch, float roll)
{
	m_camYaw = yaw;
	m_camPitch = pitch;
	m_camRoll = roll;
}

D3DXVECTOR3 CameraClass::GetPosition()
{
	return m_position;
}

D3DXVECTOR3 CameraClass::GetRotation()
{
	return D3DXVECTOR3(m_camYaw, m_camPitch, m_camRoll);
}

void CameraClass::Render()
{
	m_lookAt = m_defaultLookAt;
	m_right = m_defaultRight;

	D3DXMatrixRotationYawPitchRoll(&m_camRotationMatrix, m_camYaw, m_camPitch, m_camRoll);

	D3DXVec3TransformCoord(&m_right, &m_right, &m_camRotationMatrix);
	D3DXVec3TransformCoord(&m_lookAt, &m_lookAt, &m_camRotationMatrix);

	// Translate the rotated camera position to the location of the viewer.
	m_lookAt = m_position + m_lookAt;

	// Finally create the view matrix from the three updated vectors.
	D3DXMatrixLookAtLH(&m_viewMatrix, &m_position, &m_lookAt, &m_up);
}

void CameraClass::GetViewMatrix(D3DXMATRIX& viewMatrix)
{
	viewMatrix = m_viewMatrix;
}
