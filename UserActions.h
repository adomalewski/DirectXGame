#ifndef USERACTIONS_H
#define USERACTIONS_H

#include <string>
#include <map>

#include "inputclass.h"

using std::string;
using std::map;
using std::pair;

typedef map<string, int> KeyActionMapping;

class UserActions
{
public:
	UserActions(InputClass*);
	~UserActions();

	void InitializeKeyActionMap();

	bool IsMoveForward();
	bool IsMoveBackward();
	bool IsMoveLeft();
	bool IsMoveRight();
	bool IsJump();
	bool IsLayDown();
	bool IsCrouch();

private:
	InputClass* m_Input;
	KeyActionMapping keyActionMapping;
};

#endif // USERACTIONS_H