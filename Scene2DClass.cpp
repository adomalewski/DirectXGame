#include "Scene2DClass.h"

Scene2DClass::Scene2DClass()
{
	m_Bitmap = 0;
	m_Text = 0;
}

Scene2DClass::~Scene2DClass()
{
}

bool Scene2DClass::Initialize(D3DClass* d3d, HWND hwnd, int screenWidth, int screenHeight, TextureShaderClass* textureShader, D3DXMATRIX& viewMatrix)
{
	bool result;

	m_D3D = d3d;
	m_hwnd = hwnd;
	m_TextureShader = textureShader;
	m_ViewMatrix = viewMatrix;

	// Create the text object.
	m_Text = new TextClass;
	if (!m_Text)
	{
		return false;
	}

	// Initialize the text object.
	result = m_Text->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), m_hwnd, screenWidth, screenHeight, m_ViewMatrix);
	if (!result)
	{
		MessageBox(m_hwnd, "Could not initialize the text object.", "Error", MB_OK);
		return false;
	}

	// Create the bitmap object.
	m_Bitmap = new BitmapClass;
	if (!m_Bitmap)
	{
		return false;
	}

	// Initialize the bitmap object.
	result = m_Bitmap->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, "seafloor.dds", 256, 256);
	if (!result)
	{
		MessageBox(m_hwnd, "Could not initialize the bitmap object.", "Error", MB_OK);
		return false;
	}

	m_D3D->GetOrthoMatrix(m_OrthoMatrix);

	return true;
}

void Scene2DClass::Shutdown()
{
	// Release the text object.
	if (m_Text)
	{
		m_Text->Shutdown();
		delete m_Text;
		m_Text = 0;
	}

	// Release the bitmap object.
	if (m_Bitmap)
	{
		m_Bitmap->Shutdown();
		delete m_Bitmap;
		m_Bitmap = 0;
	}
}

void Scene2DClass::Update()
{
	bool result;

	// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->TurnZBufferOff();

	result = UpdateTextures();
	if (!result)
	{
		MessageBox(m_hwnd, "Could not update textures", "Error", MB_OK);
	}

	result = UpdateText();
	if (!result)
	{
		MessageBox(m_hwnd, "Could not update text", "Error", MB_OK);
	}

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn();
}

bool Scene2DClass::UpdateTextures()
{
	bool result;
	D3DXMATRIX textureWorldMatrix;

	D3DXMatrixIdentity(&textureWorldMatrix);

	// Put the bitmap vertex and index buffers on the graphics pipeline to prepare them for drawing.
	result = m_Bitmap->Render(m_D3D->GetDeviceContext(), 100, 100);
	if (!result)
	{
		return false;
	}

	D3DXMatrixIdentity(&textureWorldMatrix);

	// Render the bitmap with the texture shader.
	result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Bitmap->GetIndexCount(), textureWorldMatrix, m_ViewMatrix, m_OrthoMatrix, m_Bitmap->GetTexture());
	if (!result)
	{
		return false;
	}

	return true;
}

bool Scene2DClass::UpdateText()
{
	bool result;
	D3DXMATRIX textureWorldMatrix;

	D3DXMatrixIdentity(&textureWorldMatrix);

	// Turn on the alpha blending before rendering the text.
	m_D3D->TurnOnAlphaBlending();

	// Render the text strings.
	result = m_Text->Render(m_D3D->GetDeviceContext(), textureWorldMatrix, m_OrthoMatrix);
	if (!result)
	{
		return false;
	}

	// Turn off alpha blending after rendering the text.
	m_D3D->TurnOffAlphaBlending();

	return true;
}