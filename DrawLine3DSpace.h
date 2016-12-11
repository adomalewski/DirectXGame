#ifndef DRAWLINE3DSPACE_H
#define DRAWLINE3DSPACE_H

#include <boost/tuple/tuple.hpp>

#include "ColorModel.h"

class DrawLine3DSpace : public ColorModel
{
public:
    DrawLine3DSpace();
    DrawLine3DSpace(const DrawLine3DSpace&);
    ~DrawLine3DSpace();

	bool Initialize(ID3D11Device*);
    bool Render(ID3D11DeviceContext*, ColorShaderClass*, D3DXMATRIX,
        D3DXMATRIX, D3DXMATRIX);

    virtual ModelDataType CreateModelData();
};

#endif // DRAWLINE3DSPACE_H
