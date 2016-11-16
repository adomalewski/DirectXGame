#ifndef USERCAMERA_H
#define USERCAMERA_H

#include <time.h>

#include "CameraClass.h"
#include "UserActions.h"

class UserCamera : public CameraClass
{
public:
	UserCamera(UserActions*);
	~UserCamera();

	virtual void Update();

	void MoveForward();
	void MoveBackward();
	void MoveLeft();
	void MoveRight();
	void Jump();
	void LayDown();
	void Crouch();

private:
	UserActions* m_UserActions;
	float m_speedLeftRight;
	float m_speedBackForward;
	float m_diffLeftRight;
	float m_diffBackForward;
};

#endif // USERCAMERA_H