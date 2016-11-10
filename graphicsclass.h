#ifndef GRAPHICSCLASS_H
#define GRAPHICSCLASS_H

#include "d3dclass.h"
#include "cameraclass.h"
#include "colorshaderclass.h"
#include "textureshaderclass.h"
#include "lightshaderclass.h"
#include "Scene3DClass.h"
#include "Scene2DClass.h"
#include "FrameInformation.h"

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

	bool Initialize(int, int, HWND);
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
    CameraClass* m_Camera;
	ColorShaderClass* m_ColorShader;
	TextureShaderClass* m_TextureShader;
	LightShaderClass* m_LightShader;
	Scene2DClass* m_Scene2D;
	Scene3DClass* m_Scene3D;

	FrameInformation m_FrameInformation;
};

#endif // GRAPHICSCLASS_H
