#ifndef SCENE2DCLASSTEST_H
#define SCENE2DCLASSTEST_H

#include "d3dclass.h"
#include "WindowInfo.h"
//#include "TextureInfo.h"
//#include "FontTextInfo.h"
#include "TextConverter.h"
#include "FrameInformation.h"
#include "textureshaderclass.h"
#include "bitmapclass.h"

class Scene2DClassTest
{
public:
	Scene2DClassTest();
	~Scene2DClassTest();

	bool Initialize(D3DClass*, WindowInfo*, TextureShaderClass*);
	void Shutdown();

	void Update(FrameInformation);

private:
	D3DClass* m_D3D;
	WindowInfo* m_windowInfo;
	TextureShaderClass* m_TextureShader;
	BitmapClass* m_Bitmap;
};

#endif // SCENE2DCLASSTEST_H
