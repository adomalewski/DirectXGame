#include "cameraclass.h"

CameraClass::CameraClass()
{
	m_rotationX = 0.0f;
	m_rotationY = 0.0f;
	m_rotationZ = 0.0f;

	m_up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_lookAt = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	D3DXVec3Cross(&m_right, &m_lookAt, &m_up);

	D3DXVec3Normalize(&m_right, &m_right);
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

void CameraClass::SetRotation(float x, float y, float z)
{
	m_rotationX = x;
	m_rotationY = y;
	m_rotationZ = z;
}

D3DXVECTOR3 CameraClass::GetPosition()
{
	return m_position;
}

D3DXVECTOR3 CameraClass::GetRotation()
{
	return D3DXVECTOR3(m_rotationX, m_rotationY, m_rotationZ);
}

void CameraClass::Render()
{
	float yaw, pitch, roll;
	D3DXMATRIX rotationMatrix;

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	pitch = m_rotationX * 0.0174532925f;
	yaw   = m_rotationY * 0.0174532925f;
	roll  = m_rotationZ * 0.0174532925f;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, roll);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	D3DXVec3TransformCoord(&m_lookAt, &m_lookAt, &rotationMatrix);
	D3DXVec3TransformCoord(&m_up, &m_up, &rotationMatrix);

	// Translate the rotated camera position to the location of the viewer.
	m_lookAt = m_position + m_lookAt;

	D3DXVec3Cross(&m_right, &m_lookAt, &m_up);

	D3DXVec3Normalize(&m_lookAt, &m_lookAt);
	D3DXVec3Normalize(&m_right, &m_right);
	D3DXVec3Normalize(&m_up, &m_up);

	// Finally create the view matrix from the three updated vectors.
	D3DXMatrixLookAtLH(&m_viewMatrix, &m_position, &m_lookAt, &m_up);
}

void CameraClass::GetViewMatrix(D3DXMATRIX& viewMatrix)
{
	viewMatrix = m_viewMatrix;
}
