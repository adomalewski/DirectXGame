#ifndef TEXTURECLASS_H
#define TEXTURECLASS_H

#include "pch.h"

#include <d3d11.h>
#include <d3dx11tex.h>

#include "TextConverter.h"

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

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> textureTK;
};

#endif // TEXTURECLASS_H
