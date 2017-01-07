#include "Scene2DClassTest.h"

Scene2DClassTest::Scene2DClassTest()
{
    m_Bitmap = 0;
}

Scene2DClassTest::~Scene2DClassTest()
{
}

bool Scene2DClassTest::Initialize(D3DClass* d3d, WindowInfo* windowInfo, TextureShaderClass* textureShader)
{
    bool result;

	m_D3D = d3d;
	m_windowInfo = windowInfo;
	m_TextureShader = textureShader;

    // Create the bitmap object.
	m_Bitmap = new BitmapClass;
	if(!m_Bitmap)
	{
		return false;
	}

	// Initialize the bitmap object.
	result = m_Bitmap->Initialize(m_D3D->GetDevice(), m_windowInfo->m_screenWidth, m_windowInfo->m_screenHeight,
        "seafloor.dds", 256, 256);
	if(!result)
	{
		MessageBox(m_windowInfo->m_hwnd, "Could not initialize the bitmap object.", "Error", MB_OK);
		return false;
	}

	return true;
}

void Scene2DClassTest::Shutdown()
{
    // Release the bitmap object.
	if(m_Bitmap)
	{
		m_Bitmap->Shutdown();
		delete m_Bitmap;
		m_Bitmap = 0;
	}
}

void Scene2DClassTest::Update(FrameInformation frameInformation)
{
    bool result;

    m_D3D->TurnZBufferOff();

    // Put the bitmap vertex and index buffers on the graphics pipeline to prepare them for drawing.
    static int posX = 20, posY = 133;
	result = m_Bitmap->Render(m_D3D->GetDeviceContext(), posX, posY);
	if(!result)
	{
		MessageBox(NULL, "Scene2DClassTest::Update m_Bitmap->Render() problem", "Error", MB_OK);
	}

	D3DXMATRIX worldMatrix, viewMatrix, orthoMatrix, matRotation, matTranslation, matTransCenter, matRevertTransCenter;
	D3DXMatrixIdentity(&worldMatrix);
	D3DXMatrixIdentity(&viewMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);

	float centerX = m_windowInfo->m_screenWidth/2 - m_Bitmap->m_bitmapWidth/2 - posX;
	float centerY = -m_windowInfo->m_screenHeight/2 + m_Bitmap->m_bitmapHeight/2 + posY;

    D3DXMatrixTranslation(&matTransCenter, centerX, centerY, 0.0f);
    D3DXMatrixTranslation(&matRevertTransCenter, -centerX, -centerY, 0.0f);
    D3DXMatrixRotationZ(&matRotation, D3DX_PI/2);
	D3DXMatrixTranslation(&matTranslation, m_windowInfo->m_screenWidth*(frameInformation.rotation/(8*D3DX_PI)), 0.0f, 0.0f);
    worldMatrix = matTransCenter * matRotation * matRevertTransCenter * matTranslation;


	// Render the bitmap with the texture shader.
	result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Bitmap->GetIndexCount(),
        worldMatrix, viewMatrix, orthoMatrix, m_Bitmap->GetTexture());
	if(!result)
	{
		MessageBox(NULL, "Scene2DClassTest::Update m_TextureShader->Render() problem", "Error", MB_OK);
	}

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn();
}
