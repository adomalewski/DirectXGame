#ifndef AXES3DSPACE_H
#define AXES3DSPACE_H

#include "DrawLine3DSpace.h"

class Axes3DSpace
{
public:
    Axes3DSpace();
    ~Axes3DSpace();

	bool Initialize(ID3D11Device*);
    bool Render(ID3D11DeviceContext*, ColorShaderClass*, D3DXMATRIX,
        D3DXMATRIX, D3DXMATRIX);
    void Shutdown();

    ColorModel::ModelDataType CreateModelData();

private:
    DrawLine3DSpace* m_DrawLine3D;
};

#endif // AXES3DSPACE_H
