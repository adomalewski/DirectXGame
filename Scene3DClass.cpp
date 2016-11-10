#include "Scene3DClass.h"

Scene3DClass::Scene3DClass()
{
	m_Model = 0;
	m_Light = 0;
}

Scene3DClass::~Scene3DClass()
{
}

bool Scene3DClass::Initialize(D3DClass* d3d, HWND hwnd,  D3DXMATRIX& viewMatrix,
		ColorShaderClass* colorShader, TextureShaderClass* textureShader, LightShaderClass* lightShader)
{
	bool result;

	m_D3D = d3d;
	m_hwnd = hwnd;
	m_ViewMatrix = viewMatrix;
	m_ColorShader = colorShader;
	m_TextureShader = textureShader;
	m_LightShader = lightShader;

	// Create the model object.
	m_Model = new ModelClass;
	if (!m_Model)
	{
		return false;
	}

	// Initialize the model object.
	//result = m_Model->Initialize4VertexColor(m_D3D->GetDevice());
	//result = m_Model->Initialize4Texture(m_D3D->GetDevice(), "seafloor.dds");
	result = m_Model->Initialize4TextureNormal(m_D3D->GetDevice(), "seafloor.dds");
	if (!result)
	{
		MessageBox(m_hwnd, "Could not initialize the model object.", "Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if (!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetDiffuseColor(0.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(0.0f, 0.0f, 1.0f);

	return true;
}

void Scene3DClass::Shutdown()
{
	// Release the model object.
	if (m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}

	// Release the light object.
	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}
}

void Scene3DClass::Update(FrameInformation frameInformation)
{
	bool result;
	D3DXMATRIX worldMatrix, projectionMatrix;

	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	// Rotate the world matrix by the rotation value so that the triangle will spin.
	D3DXMatrixRotationY(&worldMatrix, frameInformation.rotation);

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_Model->Render(m_D3D->GetDeviceContext());

	//// Render the model using the color shader.
	//  result = m_ColorShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix);
	//// Render the model using the texture shader.
	//result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
	//	m_Model->GetTexture());
	// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, m_ViewMatrix, projectionMatrix,
		m_Model->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
	if (!result)
	{
		MessageBox(m_hwnd, "Could not render shader", "Error", MB_OK);
	}
}