#ifndef COLORMODEL_H
#define COLORMODEL_H

#include "VertexType.h"
#include "modelclass.h"

class ColorModel : public ModelClass<VertexTypeColor>
{
public:
	ColorModel();
	ColorModel(const ColorModel&);
	~ColorModel();

	bool Initialize(ID3D11Device*, VertexTypeColor*, unsigned long*, int, int);

private:
    bool InitializeBuffers(ID3D11Device*, VertexTypeColor*, unsigned long*, int, int);
};

#endif // COLORMODEL_H
