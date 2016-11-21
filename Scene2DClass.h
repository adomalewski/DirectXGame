#ifndef SCENE2DCLASS_H
#define SCENE2DCLASS_H

#include "pch.h"

#include "d3dclass.h"
#include "bitmapclass.h"
#include "textclass.h"
#include "textureshaderclass.h"

class Scene2DClass
{
public:
	Scene2DClass();
	~Scene2DClass();

	bool Initialize(D3DClass*, HWND, int , int, TextureShaderClass*, D3DXMATRIX);
	void Shutdown();

	void Update();

private:
	bool UpdateTextures();
	bool UpdateText();

private:
	D3DClass* m_D3D;
	HWND m_hwnd;
	BitmapClass* m_Bitmap;
	TextClass* m_Text;
	TextureShaderClass* m_TextureShader;

	D3DXMATRIX m_staticWorldMatrix;
	D3DXMATRIX m_staticOrthoMatrix;
	D3DXMATRIX m_staticViewMatrix;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
};

#endif // SCENE2DCLASS_H
