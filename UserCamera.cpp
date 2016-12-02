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
	int y = m_position.y;
	m_position += m_diffBackForward*(m_lookAt - m_position);
	if (m_cameraType != FreeFly)
		m_position.y = y;
}

void UserCamera::MoveBackward()
{
	int y = m_position.y;
	m_position -= m_diffBackForward*(m_lookAt - m_position);
	if (m_cameraType != FreeFly)
		m_position.y = y;
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
		m_camPitch += lY * m_speedCameraRotation;
}