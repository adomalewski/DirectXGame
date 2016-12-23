#include "Scene3DClass.h"

Scene3DClass::Scene3DClass()
{
	m_TriangleColorModel = 0;
	m_TriangleTextureModel = 0;
	m_TriangleTextureNormalModel = 0;
	m_Light = 0;
	m_SimpleSurface = 0;
	m_AppartmentModel = 0;
	m_Axes3D = 0;
}

Scene3DClass::~Scene3DClass()
{
}

bool Scene3DClass::Initialize(D3DClass* d3d, HWND hwnd, ColorShaderClass* colorShader,
    TextureShaderClass* textureShader, LightShaderClass* lightShader, MeshShaderClass* meshShader)
{
	bool result = true;

	m_D3D = d3d;
	m_hwnd = hwnd;
	m_ColorShader = colorShader;
	m_TextureShader = textureShader;
	m_LightShader = lightShader;
	m_MeshShader = meshShader;

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

	m_Axes3D = new Axes3DSpace;
	if (!m_Axes3D)
	{
		return false;
	}

	// Initialize the model objects.
	result = result && m_TriangleColorModel->Initialize(m_D3D->GetDevice());
	result = result && m_TriangleTextureModel->Initialize(m_D3D->GetDevice());
	result = result && m_TriangleTextureNormalModel->Initialize(m_D3D->GetDevice());
	result = result && m_SimpleSurface->Initialize(m_D3D->GetDevice());
	result = result && m_Axes3D->Initialize(m_D3D->GetDevice());
	if (!result)
	{
		MessageBox(m_hwnd, "Could not initialize the model object.", "Error", MB_OK);
		return false;
	}

	m_AppartmentModel = new Obj3DModel;
	if (!m_AppartmentModel)
		return false;

	if (!m_AppartmentModel->Initialize(m_D3D->GetDevice(), "spaceCompound.obj"))
		return false;

	// Create the light object.
	m_Light = new LightClass;
	if (!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetAmbientColor(0.6f, 0.6f, 0.6f, 1.0f);
	m_Light->SetDiffuseColor(0.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(0.0f, 10.0f, 0.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(3.0f);

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

	if (m_Axes3D)
	{
		m_Axes3D->Shutdown();
		delete m_Axes3D;
		m_Axes3D = 0;
	}

    if (m_AppartmentModel)
	{
		m_AppartmentModel->Shutdown();
		delete m_AppartmentModel;
		m_AppartmentModel = 0;
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
	D3DXMATRIX worldMatrix, matTranslation, matRotation, matScale, projectionMatrix;

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
        viewMatrix, projectionMatrix, m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
        frameInformation.userCameraPosition, m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

    D3DXMatrixIdentity(&worldMatrix);

    result = result && m_SimpleSurface->Render(m_D3D->GetDeviceContext(), m_LightShader, worldMatrix,
        viewMatrix, projectionMatrix, m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
        frameInformation.userCameraPosition, m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

    D3DXMatrixIdentity(&worldMatrix);

	// Get the viewport
	D3D11_VIEWPORT pViewports;
	D3D10_VIEWPORT viewport;
	UINT numViewports = 1;

	m_D3D->GetDeviceContext()->RSGetViewports(&numViewports, &pViewports);
	viewport.Width = (UINT)pViewports.Width;
	viewport.Height = (UINT)pViewports.Height;
	viewport.MinDepth = pViewports.MinDepth;
	viewport.MaxDepth = pViewports.MaxDepth;
	viewport.TopLeftX = pViewports.TopLeftX;
	viewport.TopLeftY = pViewports.TopLeftY;

	// Get the center point of the object	
	D3DXVECTOR3* p_centerPoint = new D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// Get the point on the screen that is the screen projection of the object
	D3DXVECTOR3 projectPoint;
	D3DXVec3Project(&projectPoint, p_centerPoint, &viewport, &projectionMatrix, &viewMatrix, &worldMatrix);

	// Choose the screen point where the object is to be drawn, relative to the Viewport's dimensions
	D3DXVECTOR3 screenPoint;
	screenPoint.x = 0.15*viewport.Width;
	screenPoint.y = 0.85*viewport.Height;
	screenPoint.z = 0.99f;
	//screenPoint.z = projectPoint.z; //bêdzie dziwnie zmieniaæ rozmiar obiektu

	//transform the screen position to a world position
	D3DXVECTOR3 worldPoint;
	D3DXVec3Unproject(&worldPoint, &screenPoint, &viewport, &projectionMatrix, &viewMatrix, &worldMatrix);

	// Now define how much to translate the object in order to get it to the point we want it to be (WorldPoint)
	float transX, transY, transZ;
	transX = worldPoint.x;
	transY = worldPoint.y;
	transZ = worldPoint.z;

	// apply the translation matrix
	D3DXMatrixTranslation(&worldMatrix, transX, transY, transZ);

    result = result && m_Axes3D->Render(m_D3D->GetDeviceContext(), m_ColorShader, worldMatrix,
        viewMatrix, projectionMatrix);

	D3DXMatrixTranslation(&matTranslation, 0.0f, 0.0f, 0.0f);
	D3DXMatrixRotationX(&matRotation, D3DX_PI / 8);
	D3DXMatrixScaling(&matScale, 0.1f, 0.1f, 0.1f);
	worldMatrix = matScale * matRotation * matTranslation;

	result = result && m_AppartmentModel->Render(m_D3D->GetDeviceContext(), m_D3D, m_MeshShader, worldMatrix,
		viewMatrix, projectionMatrix, m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		frameInformation.userCameraPosition, m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

	if (!result)
	{
		MessageBox(m_hwnd, "Scene3DClass::Update problem", "Error", MB_OK);
	}
}
