#include "UserCamera.h"

UserCamera::UserCamera(UserActions* userActions)
{
	m_UserActions = userActions;

	m_speedLeftRight = 0.1f;
	m_speedBackForward = 0.01f;
	m_diffLeftRight = 0.0f;
	m_diffBackForward = 0.0f;

}

UserCamera::~UserCamera()
{
}

void UserCamera::Update()
{
	time_t timeDiff;
	static time_t lastTime = time(NULL);
	timeDiff = time(NULL) - lastTime;

	if (timeDiff != 0)
	{
		m_diffBackForward = m_speedBackForward * timeDiff;
		m_diffLeftRight = m_speedLeftRight * timeDiff;
	}

	if(m_UserActions->IsMoveForward())
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

	lastTime += timeDiff;
}

void UserCamera::MoveForward()
{
	m_position -= m_diffBackForward*m_lookAt;
}

void UserCamera::MoveBackward()
{
	m_position += m_diffBackForward*m_lookAt;
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