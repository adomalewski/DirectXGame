#ifndef GRAPHICSCLASS_H
#define GRAPHICSCLASS_H

#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "colorshaderclass.h"
#include "textureshaderclass.h"
#include "lightshaderclass.h"
#include "lightclass.h"
#include "bitmapclass.h"
#include "textclass.h"

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

struct FrameInformation
{
	float rotation;
	float time;
};

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
	bool InitializeColorShader(HWND);
	bool InitializeTextureShader(HWND);
	bool InitializeLightShader(HWND);

	void ComputeRotationInFrame();

private:
    D3DClass* m_D3D;
    CameraClass* m_Camera;
	ModelClass* m_Model;
	ColorShaderClass* m_ColorShader;
	TextureShaderClass* m_TextureShader;
	LightShaderClass* m_LightShader;
	LightClass* m_Light;
	BitmapClass* m_Bitmap;
	TextClass* m_Text;
	FrameInformation frameInformation;
};

#endif // GRAPHICSCLASS_H
