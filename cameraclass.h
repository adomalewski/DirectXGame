#ifndef CAMERACLASS_H
#define CAMERACLASS_H

#include <d3dx10math.h>

class CameraClass
{
public:
	CameraClass();
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
	float m_rotationX, m_rotationY, m_rotationZ;
	D3DXVECTOR3 m_up, m_position, m_lookAt, m_right;
	D3DXMATRIX m_viewMatrix;
};

#endif // CAMERACLASS_H
