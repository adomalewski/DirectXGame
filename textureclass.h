#ifndef TEXTURECLASS_H_INCLUDED
#define TEXTURECLASS_H_INCLUDED

#include <d3d11.h>
#include <d3dx11tex.h>

class TextureClass
{
public:
	TextureClass();
	TextureClass(const TextureClass&);
	~TextureClass();

	bool Initialize(ID3D11Device*, LPCSTR);
	void Shutdown();

    ID3D11ShaderResourceView* GetTexture();

private:
    ID3D11ShaderResourceView* m_texture;
};

#endif // TEXTURECLASS_H_INCLUDED
