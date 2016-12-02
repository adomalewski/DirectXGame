#ifndef CAMERACLASS_H
#define CAMERACLASS_H

#include <d3dx10math.h>

enum CameraType { FirstPerson, ThirdPerson, OnlyMove, OnlyWatch, OnlyPitch, OnlyYaw, OnlyRotate, FreeFly };

class CameraClass
{
public:
	CameraClass(CameraType);
	CameraClass(const CameraClass&);
	~CameraClass();

	void SetPosition(float, float, float);
	void SetRotation(float, float, float);

	D3DXVECTOR3 GetPosition();
	D3DXVECTOR3 GetRotation();

	virtual void Update() = 0;
	void Render();
	void GetViewMatrix(D3DXMATRIX&);

protected:
	D3DXVECTOR3 m_up, m_position, m_lookAt, m_right;
	D3DXVECTOR3 m_defaultRight, m_defaultLookAt;
	D3DXMATRIX m_viewMatrix;
	CameraType m_cameraType;

	D3DXMATRIX m_camRotationMatrix;

	float m_camYaw;
	float m_camPitch;
	float m_camRoll;
};

#endif // CAMERACLASS_H
