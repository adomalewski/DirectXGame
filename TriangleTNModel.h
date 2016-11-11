#ifndef TRIANGLETNMODEL_H
#define TRIANGLETNMODEL_H

//#include <d3d11.h>
//#include <d3dx10math.h>

#include "modelclass.h"
#include "textureclass.h"

class TriangleTNModel : public ModelClass
{
private:
	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
		D3DXVECTOR3 normal;
	};
};

#endif // TRIANGLETNMODEL_H
