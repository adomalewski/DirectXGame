#include "UserCamera.h"

UserCamera::UserCamera(UserActions* userActions, CameraType cameraType = FirstPerson)
	: CameraClass(cameraType)
{
	m_UserActions = userActions;

	m_speedLeftRight = 0.1f;
	m_speedBackForward = 0.1f;
	m_diffLeftRight = 0.0f;
	m_diffBackForward = 0.0f;
	m_speedCameraRotation = 0.002f;
}

UserCamera::~UserCamera()
{
}

void UserCamera::Update()
{
	if (m_cameraType != OnlyWatch)
	{
		time_t timeDiff;
		static time_t lastTime = time(NULL);
		timeDiff = time(NULL) - lastTime;

		if (timeDiff != 0)
		{
			m_diffBackForward = m_speedBackForward * timeDiff;
			m_diffLeftRight = m_speedLeftRight * timeDiff;
		}

		//it should be updating sth like: Game->TakeCurrentContext()->UpdateUserActions()

		if (m_cameraType != OnlyPitch && m_cameraType != OnlyYaw && m_cameraType != OnlyRotate)
		{
			if (m_UserActions->IsMoveForward())
				MoveForward();
			if (m_UserActions->IsMoveBackward())
				MoveBackward();
			if (m_UserActions->IsMoveLeft())
				MoveLeft();
			if (m_UserActions->IsMoveRight())
				MoveRight();
			if (m_UserActions->IsJump())
				Jump();
			if (m_UserActions->IsLayDown())
				LayDown();
			if (m_UserActions->IsCrouch())
				Crouch();
			if (m_UserActions->IsFire())
				Fire();
			if (m_UserActions->IsZoom())
				Zoom();
		}

		if (m_cameraType != OnlyMove)
		{
			if (m_UserActions->IsMouseMoved())
				RotateCamera();
		}

		lastTime += timeDiff;
	}
}

void UserCamera::MoveForward()
{
	D3DXVECTOR3 moveVector = m_lookAt - m_position;
	if(m_cameraType != FreeFly)
        MakeMoveVectorForFlatMovement(moveVector);

	m_position += m_diffBackForward*moveVector;
}

void UserCamera::MoveBackward()
{
	D3DXVECTOR3 moveVector = m_lookAt - m_position;
	if(m_cameraType != FreeFly)
        MakeMoveVectorForFlatMovement(moveVector);

	m_position -= m_diffBackForward*moveVector;
}

void UserCamera::MoveLeft()
{
	m_position += m_right*m_diffLeftRight;
}

void UserCamera::MoveRight()
{
	m_position -= m_right*m_diffLeftRight;
}

void UserCamera::Jump()
{

}

void UserCamera::LayDown()
{

}

void UserCamera::Crouch()
{

}

void UserCamera::Fire()
{

}

void UserCamera::Zoom()
{

}

void UserCamera::RotateCamera()
{
	int lX, lY;
	m_UserActions->GetMouselXY(lX, lY);

	if(m_cameraType != OnlyPitch)
		m_camYaw += lX * m_speedCameraRotation;

	if (m_cameraType != OnlyYaw)
	{
        float tmpPitch = m_camPitch + lY * m_speedCameraRotation;
        if(!((m_camPitch < D3DX_PI/2 && tmpPitch >= D3DX_PI/2) ||
            (m_camPitch > -D3DX_PI/2 && tmpPitch <= -D3DX_PI/2)))
            m_camPitch += lY * m_speedCameraRotation;
    }
}

void UserCamera::MakeMoveVectorForFlatMovement(D3DXVECTOR3& vec)
{
    float x, z;
    if(vec.x == 0)
        z = vec.z/std::abs(vec.z);
    if(vec.z == 0)
        x = vec.x/std::abs(vec.x);
    if(vec.x != 0 && vec.z != 0)
    {
        z = (vec.z/std::abs(vec.z))*std::sqrt(1/(1.0f + std::pow(vec.x/vec.z, 2)));
        x = (vec.x/vec.z)*z;
        x = (vec.x/std::abs(vec.x))*std::abs(x);
    }

    vec = D3DXVECTOR3(x, 0.0f, z);
}
