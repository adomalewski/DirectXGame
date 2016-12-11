#ifndef TRIANGLECOLORMODEL_H
#define TRIANGLECOLORMODEL_H

#include <boost/tuple/tuple.hpp>

#include "ColorModel.h"

class TriangleColorModel : public ColorModel
{
public:
	TriangleColorModel();
	TriangleColorModel(const TriangleColorModel&);
	~TriangleColorModel();

	bool Initialize(ID3D11Device*);

    virtual ModelDataType CreateModelData();
};

#endif // TRIANGLECOLORMODEL_H
