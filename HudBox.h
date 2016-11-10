#ifndef HUDBOX_H
#define HUDBOX_H

#include "textclass.h"

class HudBox
{
public:
	HudBox();
	~HudBox();

private:
	TextClass* m_Text;
};

#endif // HUDBOX_H