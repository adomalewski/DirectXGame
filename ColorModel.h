#ifndef COLORMODEL_H
#define COLORMODEL_H

#include <boost/tuple/tuple.hpp>

#include "VertexType.h"
#include "ColorShaderClass.h"
#include "modelclass.h"

class ColorModel : public ModelClass<VertexTypeColor>
{
public:
    typedef boost::tuple<VertexTypeColor*, unsigned long*, int, int> ModelDataType;

	ColorModel();
	ColorModel(const ColorModel&);
	~ColorModel();

	bool Initialize(ID3D11Device*, VertexTypeColor*, unsigned long*, int, int);
	bool Render(ID3D11DeviceContext*, ColorShaderClass*, D3DXMATRIX,
        D3DXMATRIX, D3DXMATRIX,
        D3D_PRIMITIVE_TOPOLOGY primitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    void ReleaseModelData(VertexTypeColor*, unsigned long*);

    virtual ModelDataType CreateModelData() = 0;

private:
    bool InitializeBuffers(ID3D11Device*, VertexTypeColor*, unsigned long*, int, int);
};

#endif // COLORMODEL_H
