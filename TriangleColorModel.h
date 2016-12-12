#ifndef TRIANGLECOLORMODEL_H
#define TRIANGLECOLORMODEL_H

#include "ColorModel.h"

class TriangleColorModel : public ColorModel
{
public:
	TriangleColorModel();
	TriangleColorModel(const TriangleColorModel&);
	~TriangleColorModel();

	bool Initialize(ID3D11Device*);

    ModelDataType CreateModelData();
};

#endif // TRIANGLECOLORMODEL_H
