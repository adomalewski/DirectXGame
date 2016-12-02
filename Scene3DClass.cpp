#include "Scene3DClass.h"

Scene3DClass::Scene3DClass()
{
	m_TriangleColorModel = 0;
	m_TriangleTextureModel = 0;
	m_TriangleTextureNormalModel = 0;
	m_Light = 0;
	m_SimpleSurface = 0;
	m_appartmentModel = 0;
}

Scene3DClass::~Scene3DClass()
{
}

bool Scene3DClass::Initialize(D3DClass* d3d, HWND hwnd, ColorShaderClass* colorShader,
    TextureShaderClass* textureShader, LightShaderClass* lightShader)
{
	bool result = true;

	m_D3D = d3d;
	m_hwnd = hwnd;
	m_ColorShader = colorShader;
	m_TextureShader = textureShader;
	m_LightShader = lightShader;

	m_TriangleColorModel = new TriangleColorModel;
	if (!m_TriangleColorModel)
	{
		return false;
	}

    m_TriangleTextureModel = new TriangleTextureModel;
	if (!m_TriangleTextureModel)
	{
		return false;
	}

    m_TriangleTextureNormalModel = new TriangleTextureNormalModel;
	if (!m_TriangleTextureNormalModel)
	{
		return false;
	}

    m_SimpleSurface = new SimpleSurface;
	if (!m_SimpleSurface)
	{
		return false;
	}

	// Initialize the model object.
	result = result && m_TriangleColorModel->Initialize(m_D3D->GetDevice());
	result = result && m_TriangleTextureModel->Initialize(m_D3D->GetDevice());
	result = result && m_TriangleTextureNormalModel->Initialize(m_D3D->GetDevice());
	result = result && m_SimpleSurface->Initialize(m_D3D->GetDevice());
	if (!result)
	{
		MessageBox(m_hwnd, "Could not initialize the model object.", "Error", MB_OK);
		return false;
	}

	m_appartmentModel = new Obj3DModel;
	if (!m_appartmentModel)
	{
		return false;
	}

	if (!LoadObjModel(m_D3D->GetDevice(), "spaceCompound.obj", &meshVertBuff, &meshIndexBuff, meshSubsetIndexStart, meshSubsetTexture, material, meshSubsets, true, false))
		return false;
https://www.braynzarsoft.net/viewtutorial/q16390-22-loading-static-3d-models-obj-format

	// Create the light object.
	m_Light = new LightClass;
	if (!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetDiffuseColor(0.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(0.0f, -1.0f, 1.0f);

	return true;
}

void Scene3DClass::Shutdown()
{
	if (m_TriangleColorModel)
	{
		m_TriangleColorModel->Shutdown();
		delete m_TriangleColorModel;
		m_TriangleColorModel = 0;
	}

    if (m_TriangleTextureModel)
	{
		m_TriangleTextureModel->Shutdown();
		delete m_TriangleTextureModel;
		m_TriangleTextureModel = 0;
	}

    if (m_TriangleTextureNormalModel)
	{
		m_TriangleTextureNormalModel->Shutdown();
		delete m_TriangleTextureNormalModel;
		m_TriangleTextureNormalModel = 0;
	}

	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	if (m_SimpleSurface)
	{
		m_SimpleSurface->Shutdown();
		delete m_SimpleSurface;
		m_SimpleSurface = 0;
	}
}

void Scene3DClass::Update(FrameInformation frameInformation, D3DXMATRIX viewMatrix)
{
	bool result = true;
	D3DXMATRIX worldMatrix, matTranslation, matRotation, projectionMatrix;

	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	D3DXMatrixRotationY(&matRotation, frameInformation.rotation);
    worldMatrix = matRotation;

    result = result && m_TriangleColorModel->Render(m_D3D->GetDeviceContext(), m_ColorShader, worldMatrix,
        viewMatrix, projectionMatrix);

    D3DXMatrixIdentity(&worldMatrix);
	D3DXMatrixTranslation(&matTranslation, -4.0f, 0.0f, 0.0f);
	worldMatrix = matRotation * matTranslation;

    result = result && m_TriangleTextureModel->Render(m_D3D->GetDeviceContext(), m_TextureShader, worldMatrix,
        viewMatrix, projectionMatrix);

    D3DXMatrixIdentity(&worldMatrix);
	D3DXMatrixTranslation(&matTranslation, 4.0f, 0.0f, 0.0f);
	worldMatrix = matRotation * matTranslation;

    result = result && m_TriangleTextureNormalModel->Render(m_D3D->GetDeviceContext(), m_LightShader, worldMatrix,
        viewMatrix, projectionMatrix, m_Light->GetDirection(), m_Light->GetDiffuseColor());

    D3DXMatrixIdentity(&worldMatrix);
    result = result && m_SimpleSurface->Render(m_D3D->GetDeviceContext(), m_LightShader, worldMatrix,
        viewMatrix, projectionMatrix, m_Light->GetDirection(), m_Light->GetDiffuseColor());

	if (!result)
	{
		MessageBox(m_hwnd, "Could not render shader", "Error", MB_OK);
	}
}
