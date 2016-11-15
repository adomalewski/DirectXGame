#ifndef TEXTURENORMALMODEL_H
#define TEXTURENORMALMODEL_H

#include "modelclass.h"
#include "TextureModel.h"
#include "VertexType.h"

class TextureNormalModel : public TextureModel<VertexTypeTextureNormal>
{
public:
	TextureNormalModel();
	TextureNormalModel(const TextureNormalModel&);
	~TextureNormalModel();

	bool Initialize(ID3D11Device*, LPCSTR, VertexTypeTextureNormal*, unsigned long*, int, int);

private:
    bool InitializeBuffers(ID3D11Device*, VertexTypeTextureNormal*, unsigned long*, int, int);
};

#endif // TEXTURENORMALMODEL_H
