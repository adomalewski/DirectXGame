#ifndef SCENE2DCLASS_H
#define SCENE2DCLASS_H

#include "pch.h"

#include "d3dclass.h"
#include "WindowInfo.h"
#include "TextureInfo.h"
#include "FontTextInfo.h"
#include "TextConverter.h"

class Scene2DClass
{
public:
	Scene2DClass();
	~Scene2DClass();

	bool Initialize(D3DClass*, WindowInfo*);
	void Shutdown();

	void Update();

private:
	void InitializeTexture(TextureInfo&, LPCSTR);
	void InitializeFont(FontInfo&, LPCSTR);

	void SetTextureAttributes(TextureInfo&, int, int, float);
	void SetTextureAttributes(TextureInfo&, WindowRegion, float);

	void SetTextAttributes(TextInfo&, const FontInfo&, LPCSTR, int, int);

private:
	D3DClass* m_D3D;
	WindowInfo* m_windowInfo;
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;

	TextureInfo m_textureStonehenge;
	FontInfo m_fontCurierNew32;
	TextInfo m_simpleText;
};

#endif // SCENE2DCLASS_H
