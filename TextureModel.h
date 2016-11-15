#ifndef TEXTUREMODEL_H
#define TEXTUREMODEL_H

#include "VertexType.h"
#include "modelclass.h"
#include "textureclass.h"

template <typename VertexType>
class TextureModel : public ModelClass<VertexType>
{
public:
	TextureModel();
	TextureModel(const TextureModel&);
	~TextureModel();

	bool Initialize(ID3D11Device*, LPCSTR, VertexTypeTexture*, unsigned long*, int, int);
	void Shutdown();

	ID3D11ShaderResourceView* GetTexture();

protected:
	bool LoadTexture(ID3D11Device*, LPCSTR);
	void ReleaseTexture();

private:
    bool InitializeBuffers(ID3D11Device*, VertexTypeTexture*, unsigned long*, int, int);

protected:
	TextureClass* m_Texture;
};

#endif // TEXTUREMODEL_H
