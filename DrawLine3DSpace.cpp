#include "DrawLine3DSpace.h"

DrawLine3DSpace::DrawLine3DSpace()
{
}

DrawLine3DSpace::DrawLine3DSpace(const DrawLine3DSpace& other)
{
}

DrawLine3DSpace::~DrawLine3DSpace()
{
}

bool DrawLine3DSpace::Initialize(ID3D11Device* device, ModelDataType modelData)
{
	return ColorModel::Initialize(device, modelData.get<0>(), modelData.get<1>(),
        modelData.get<2>(), modelData.get<3>());
}

bool DrawLine3DSpace::Render(ID3D11DeviceContext* deviceContext, ColorShaderClass* colorShader, D3DXMATRIX worldMatrix,
			      D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix)
{
    return ColorModel::Render(deviceContext, colorShader, worldMatrix, viewMatrix, projectionMatrix,
        D3D_PRIMITIVE_TOPOLOGY_LINELIST);
}
