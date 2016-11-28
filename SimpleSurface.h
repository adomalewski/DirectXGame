#ifndef SIMPLESURFACE_H
#define SIMPLESURFACE_H

#include "TextureNormalModel.h"
#include "LightShaderClass.h"
#include <boost/tuple/tuple.hpp>

class SimpleSurface
{
private:
    typedef boost::tuple<VertexTypeTextureNormal*, unsigned long*, int, int> ModelDataType;

public:
	SimpleSurface();
	SimpleSurface(const SimpleSurface&);
	~SimpleSurface();

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

#endif // SIMPLESURFACE_H
