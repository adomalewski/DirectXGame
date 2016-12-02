#ifndef TRIANGLETEXTUREMODEL_H
#define TRIANGLETEXTUREMODEL_H

#include "TextureModel.h"
#include "TextureShaderClass.h"
#include <boost/tuple/tuple.hpp>

class TriangleTextureModel
{
public:
	typedef boost::tuple<VertexTypeTexture*, unsigned long*, int, int> ModelDataType;

	TriangleTextureModel();
	TriangleTextureModel(const TriangleTextureModel&);
	~TriangleTextureModel();

	bool Initialize(ID3D11Device*);
	void Shutdown();

	bool Render(ID3D11DeviceContext*, TextureShaderClass*, D3DXMATRIX,
        D3DXMATRIX, D3DXMATRIX);

private:
    ModelDataType CreateModelData();
    void ReleaseModelData(VertexTypeTexture*, unsigned long*);

private:
    TextureModel<VertexTypeTexture>* m_TextureModel;
};

#endif // TRIANGLETEXTUREMODEL_H
