#include "UserActions.h"

UserActions::UserActions(InputClass* input)
{
	m_Input = input;
}

UserActions::~UserActions()
{
}

void UserActions::Initialize()
{
	keyActionMapping.insert(pair<string, int>("MoveForward", DIK_W));
	keyActionMapping.insert(pair<string, int>("MoveBackward", DIK_S));
	keyActionMapping.insert(pair<string, int>("MoveLeft", DIK_A));
	keyActionMapping.insert(pair<string, int>("MoveRight", DIK_D));
	keyActionMapping.insert(pair<string, int>("Jump", DIK_SPACE));
	keyActionMapping.insert(pair<string, int>("LayDown", DIK_Z));
	keyActionMapping.insert(pair<string, int>("Crouch", DIK_C));

	keyActionMapping.insert(pair<string, int>("Fire", MOUSE_LEFT));
	keyActionMapping.insert(pair<string, int>("Zoom", MOUSE_RIGHT));
}

bool UserActions::IsMoveForward()
{
	return m_Input->IsKeyPressed(keyActionMapping.find("MoveForward")->second);
}

bool UserActions::IsMoveBackward()
{
	return m_Input->IsKeyPressed(keyActionMapping.find("MoveBackward")->second);
}

bool UserActions::IsMoveLeft()
{
	return m_Input->IsKeyPressed(keyActionMapping.find("MoveLeft")->second);
}

bool UserActions::IsMoveRight()
{
	return m_Input->IsKeyPressed(keyActionMapping.find("MoveRight")->second);
}

bool UserActions::IsJump()
{
	return m_Input->IsKeyPressed(keyActionMapping.find("Jump")->second);
}

bool UserActions::IsLayDown()
{
	return m_Input->IsKeyPressed(keyActionMapping.find("LayDown")->second);
}

bool UserActions::IsCrouch()
{
	return m_Input->IsKeyPressed(keyActionMapping.find("Crouch")->second);
}

bool UserActions::IsFire()
{
	return m_Input->IsMouseButtonPressed(keyActionMapping.find("Fire")->second);
}

bool UserActions::IsZoom()
{
	return m_Input->IsMouseButtonPressed(keyActionMapping.find("Zoom")->second);
}