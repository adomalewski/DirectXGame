#ifndef DRAWLINE3DSPACE_H
#define DRAWLINE3DSPACE_H

#include "ColorModel.h"

class DrawLine3DSpace : public ColorModel
{
public:
    DrawLine3DSpace();
    DrawLine3DSpace(const DrawLine3DSpace&);
    ~DrawLine3DSpace();

	bool Initialize(ID3D11Device*, ModelDataType);
    bool Render(ID3D11DeviceContext*, ColorShaderClass*, D3DXMATRIX,
        D3DXMATRIX, D3DXMATRIX);
};

#endif // DRAWLINE3DSPACE_H
