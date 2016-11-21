#ifndef GRAPHICSCLASS_H
#define GRAPHICSCLASS_H

#include "Scene2DClass.h"
#include "d3dclass.h"
#include "colorshaderclass.h"
#include "textureshaderclass.h"
#include "lightshaderclass.h"
#include "Scene3DClass.h"
#include "FrameInformation.h"
#include "InputClass.h"
#include "UserCamera.h"

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND, InputClass*);
	void Shutdown();

	bool Frame();
	bool Render();

private:
	bool InitializeColorShader();
	bool InitializeTextureShader();
	bool InitializeLightShader();

	void ComputeRotationInFrame();

private:
    D3DClass* m_D3D;
	HWND m_hwnd;
	ColorShaderClass* m_ColorShader;
	TextureShaderClass* m_TextureShader;
	LightShaderClass* m_LightShader;
	Scene2DClass* m_Scene2D;
	Scene3DClass* m_Scene3D;
	InputClass* m_Input;
	UserCamera* m_UserCamera;
	UserActions* m_UserActions;

	FrameInformation m_FrameInformation;
};

#endif // GRAPHICSCLASS_H
