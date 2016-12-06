#ifndef TRIANGLETEXTURENORMALMODEL_H
#define TRIANGLETEXTURENORMALMODEL_H

#include "TextureNormalModel.h"
#include "LightShaderClass.h"

typedef TextureNormalModel::ModelDataType ModelDataType;

class TriangleTextureNormalModel
{
public:
	TriangleTextureNormalModel();
	TriangleTextureNormalModel(const TriangleTextureNormalModel&);
	~TriangleTextureNormalModel();

	bool Initialize(ID3D11Device*);
	void Shutdown();

	bool Render(ID3D11DeviceContext*, LightShaderClass*, D3DXMATRIX,
        D3DXMATRIX, D3DXMATRIX, D3DXVECTOR3, D3DXVECTOR4, D3DXVECTOR4, D3DXVECTOR3,
        D3DXVECTOR4, float);

private:
    ModelDataType CreateModelData();
    void ReleaseModelData(VertexTypeTextureNormal*, unsigned long*);

private:
    TextureNormalModel* m_TextureNormalModel;
};

#endif // TRIANGLETEXTURENORMALMODEL_H
