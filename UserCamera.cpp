#include "UserCamera.h"

UserCamera::UserCamera(UserActions* userActions)
{
	m_UserActions = userActions;

	m_diffLeftRight = 0.1f;
	m_diffBackForward = 0.1f;
}

UserCamera::~UserCamera()
{
}

void UserCamera::Update()
{
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
	m_position -= m_right*m_diffLeftRight;
}

void UserCamera::MoveRight()
{
	m_position += m_right*m_diffLeftRight;
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