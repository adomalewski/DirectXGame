#include "Scene2DClass.h"

Scene2DClass::Scene2DClass()
{

}

Scene2DClass::~Scene2DClass()
{
}

bool Scene2DClass::Initialize(D3DClass* d3d, WindowInfo* windowInfo)
{
	m_D3D = d3d;
	m_windowInfo = windowInfo;

	m_spriteBatch.reset(new SpriteBatch(m_D3D->GetDeviceContext()));

	InitializeTexture(m_textureStonehenge, "Stonehenge.jpg");
	SetTextureAttributes(m_textureStonehenge, WindowRegion::TopLeft, 0.3f);

	InitializeFont(m_fontCurierNew32, "myfile.spritefont");

	SetTextAttributes(m_simpleText, m_fontCurierNew32, "Hello World", 0, 0);

	return true;
}

void Scene2DClass::Shutdown()
{
	m_spriteBatch.release();
	m_textureStonehenge.texture.Reset();
	m_fontCurierNew32.font.release();
}

void Scene2DClass::Update()
{
	std::unique_ptr<DirectX::CommonStates> m_states;
	m_states.reset(new CommonStates(m_D3D->GetDevice()));

	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states->NonPremultiplied());

	m_spriteBatch->Draw(m_textureStonehenge.texture.Get(), m_textureStonehenge.screenPos, 
		nullptr, Colors::White, 0.f, m_textureStonehenge.origin, m_textureStonehenge.scale);

	m_spriteBatch->End();

	m_spriteBatch->Begin();

	m_fontCurierNew32.font->DrawString(m_spriteBatch.get(), m_simpleText.text,
		m_simpleText.screenPos + Vector2(1.f, 1.f), Colors::Black, 0.f, m_simpleText.origin);
	m_fontCurierNew32.font->DrawString(m_spriteBatch.get(), m_simpleText.text,
		m_simpleText.screenPos + Vector2(-1.f, 1.f), Colors::Black, 0.f, m_simpleText.origin);

	m_fontCurierNew32.font->DrawString(m_spriteBatch.get(), m_simpleText.text,
		m_simpleText.screenPos, Colors::White, 0.f, m_simpleText.origin);

	m_spriteBatch->End();
}

void Scene2DClass::InitializeTexture(TextureInfo& textureInfo, LPCSTR file)
{
	makeWChar(textureInfo.file, file);

	ComPtr<ID3D11Resource> resource;
	CreateWICTextureFromFile(m_D3D->GetDevice(), textureInfo.file, resource.GetAddressOf(),
		textureInfo.texture.ReleaseAndGetAddressOf());

	ComPtr<ID3D11Texture2D> cat;
	resource.As(&cat);

	cat->GetDesc(&textureInfo.catDesc);
}

void Scene2DClass::InitializeFont(FontInfo& fontInfo, LPCSTR file)
{
	makeWChar(fontInfo.file, file);
	fontInfo.font.reset(new SpriteFont(m_D3D->GetDevice(), fontInfo.file));
}

void Scene2DClass::SetTextureAttributes(TextureInfo& textureInfo, int posScreenX, int posScreenY, float scale)
{
	textureInfo.screenPos.x = float(textureInfo.catDesc.Width / (2 / scale)) + posScreenX;
	textureInfo.screenPos.y = float(textureInfo.catDesc.Height / (2 / scale)) + posScreenY;
	textureInfo.origin.x = float(textureInfo.catDesc.Width / 2);
	textureInfo.origin.y = float(textureInfo.catDesc.Height / 2);
	textureInfo.scale = scale;
}

void Scene2DClass::SetTextureAttributes(TextureInfo& textureInfo, WindowRegion windowRegion, float scale)
{
	textureInfo.origin.x = float(textureInfo.catDesc.Width / 2);
	textureInfo.origin.y = float(textureInfo.catDesc.Height / 2);
	textureInfo.scale = scale;

	switch (windowRegion)
	{
		case TopLeft:
			textureInfo.screenPos.x = textureInfo.origin.x * scale;
			textureInfo.screenPos.y = textureInfo.origin.y * scale;
			break;
		case TopRight:
			textureInfo.screenPos.x = m_windowInfo->m_screenWidth - textureInfo.origin.x * scale;
			textureInfo.screenPos.y = textureInfo.origin.y * scale;
			break;
		case BottomLeft:
			textureInfo.screenPos.x = textureInfo.origin.x * scale;
			textureInfo.screenPos.y = m_windowInfo->m_screenHeight - textureInfo.origin.y * scale;
			break;
		case BottomRight:
			textureInfo.screenPos.x = m_windowInfo->m_screenWidth - textureInfo.origin.x * scale;
			textureInfo.screenPos.y = m_windowInfo->m_screenHeight - textureInfo.origin.y * scale;
			break;
		case Center:
			textureInfo.screenPos.x = m_windowInfo->m_screenWidth / 2.f;
			textureInfo.screenPos.y = m_windowInfo->m_screenHeight / 2.f;
			break;
		case CenterTop:
			textureInfo.screenPos.x = m_windowInfo->m_screenWidth / 2.f;
			textureInfo.screenPos.y = textureInfo.origin.y * scale;
			break;
		case CenterBottom:
			textureInfo.screenPos.x = m_windowInfo->m_screenWidth / 2.f;
			textureInfo.screenPos.y = m_windowInfo->m_screenHeight - textureInfo.origin.y * scale;
			break;
		case CenterLeft:
			textureInfo.screenPos.x = textureInfo.origin.x * scale;
			textureInfo.screenPos.y = m_windowInfo->m_screenHeight / 2.f;
			break;
		case CenterRight:
			textureInfo.screenPos.x = m_windowInfo->m_screenWidth - textureInfo.origin.x * scale;
			textureInfo.screenPos.y = m_windowInfo->m_screenHeight / 2.f;
			break;
	}
}

void Scene2DClass::SetTextAttributes(TextInfo& textInfo, const FontInfo& fontInfo, LPCSTR text, int posScreenX, int posScreenY)
{
	makeWChar(textInfo.text, text);
	textInfo.strMeasure = fontInfo.font->MeasureString(textInfo.text);
	textInfo.origin = textInfo.strMeasure / 2.f;
	textInfo.screenPos.x = posScreenX;
	textInfo.screenPos.y = posScreenY;
}
