#ifndef TRIANGLECOLORMODEL_H
#define TRIANGLECOLORMODEL_H

#include "ColorModel.h"
#include "ColorShaderClass.h"
#include <boost/tuple/tuple.hpp>

using boost::make_tuple;
using boost::tuple;

class TriangleColorModel
{
private:
    typedef tuple<VertexTypeColor*, unsigned long*, int, int> ModelDataType;

public:
	TriangleColorModel();
	TriangleColorModel(const TriangleColorModel&);
	~TriangleColorModel();

	bool Initialize(ID3D11Device*);
	void Shutdown();

	bool Render(ID3D11DeviceContext*, ColorShaderClass*, D3DXMATRIX,
        D3DXMATRIX, D3DXMATRIX);

private:
    ModelDataType CreateModelData();
    void ReleaseModelData(VertexTypeColor*, unsigned long*);

private:
    ColorModel* m_ColorModel;
};

#endif // TRIANGLECOLORMODEL_H
