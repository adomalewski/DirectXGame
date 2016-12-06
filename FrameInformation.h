#ifndef FRAMEINFORMATION_H
#define FRAMEINFORMATION_H

#include <d3dx10math.h>

struct FrameInformation
{
	float rotation;
	float time;

    D3DXVECTOR3 userCameraPosition;
};

#endif // FRAMEINFORMATION_H
