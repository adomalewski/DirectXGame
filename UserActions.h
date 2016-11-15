#ifndef USERACTIONS_H
#define USERACTIONS_H

#include <string>
#include <map>

#include "inputclass.h"
#include "InputActions.h"

using std::string;
using std::map;
using std::pair;

typedef map<string, int> KeyActionMapping;

class UserActions : public InputActions
{
public:
	UserActions(InputClass*);
	~UserActions();

	virtual void Initialize();

	bool IsMoveForward();
	bool IsMoveBackward();
	bool IsMoveLeft();
	bool IsMoveRight();
	bool IsJump();
	bool IsLayDown();
	bool IsCrouch();
};

#endif // USERACTIONS_H