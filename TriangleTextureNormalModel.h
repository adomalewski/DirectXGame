#ifndef TRIANGLETEXTURENORMALMODEL_H
#define TRIANGLETEXTURENORMALMODEL_H

#include "TextureNormalModel.h"
#include "LightShaderClass.h"
#include <boost/tuple/tuple.hpp>

using boost::make_tuple;
using boost::tuple;

class TriangleTextureNormalModel
{
private:
    typedef boost::tuple<VertexTypeTextureNormal*, unsigned long*, int, int> ModelDataType;

public:
	TriangleTextureNormalModel();
	TriangleTextureNormalModel(const TriangleTextureNormalModel&);
	~TriangleTextureNormalModel();

	bool Initialize(ID3D11Device*);
	void Shutdown();

	bool Render(ID3D11DeviceContext*, LightShaderClass*, D3DXMATRIX,
        D3DXMATRIX, D3DXMATRIX, D3DXVECTOR3, D3DXVECTOR4);

private:
    ModelDataType CreateModelData();
    void ReleaseModelData(VertexTypeTextureNormal*, unsigned long*);

private:
    TextureNormalModel* m_TextureNormalModel;
};

#endif // TRIANGLETEXTURENORMALMODEL_H
