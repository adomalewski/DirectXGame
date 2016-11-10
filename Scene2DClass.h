#ifndef SCENE2DCLASS_H
#define SCENE2DCLASS_H

#include "d3dclass.h"
#include "bitmapclass.h"
#include "textclass.h"
#include "textureshaderclass.h"

class Scene2DClass
{
public:
	Scene2DClass();
	~Scene2DClass();

	bool Initialize(D3DClass*, HWND, int , int, TextureShaderClass*, D3DXMATRIX&);
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

	D3DXMATRIX m_OrthoMatrix;
	D3DXMATRIX m_ViewMatrix;
};

#endif // SCENE2DCLASS_H