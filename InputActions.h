#ifndef INPUTACTIONS_H
#define INPUTACTIONS_H

#include <string>
#include <map>

#include "inputclass.h"

using std::string;
using std::map;
using std::pair;

typedef map<string, int> KeyActionMapping;

class InputActions
{
public:
	virtual void Initialize() = 0;
	bool IsMouseMoved() { return m_Input->IsMouseMoved(); }
	void GetMouselXY(int& mouselX, int& mouselY) { m_Input->GetMouselXY(mouselX, mouselY); }

protected:
	InputClass* m_Input;
	KeyActionMapping keyActionMapping;
};

#endif // INPUTACTIONS_H