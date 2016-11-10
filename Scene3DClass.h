#ifndef SCENE3DCLASS_H
#define SCENE3DCLASS_H

#include "d3dclass.h"
#include "modelclass.h"
#include "colorshaderclass.h"
#include "textureshaderclass.h"
#include "lightshaderclass.h"
#include "lightclass.h"
#include "FrameInformation.h"

class Scene3DClass
{
public:
	Scene3DClass();
	~Scene3DClass();

	bool Initialize(D3DClass* m_D3D, HWND hwnd, D3DXMATRIX&, ColorShaderClass*, TextureShaderClass*, LightShaderClass*);
	void Shutdown();

	void Update(FrameInformation);

private:
	D3DClass* m_D3D;
	HWND m_hwnd;
	ModelClass* m_Model;
	ColorShaderClass* m_ColorShader;
	TextureShaderClass* m_TextureShader;
	LightShaderClass* m_LightShader;
	LightClass* m_Light;

	D3DXMATRIX m_ViewMatrix;
};

#endif // SCENE3DCLASS_H