#include "graphicsclass.h"

GraphicsClass::GraphicsClass()
{
    m_D3D = 0;
    m_windowInfo = 0;
    m_UserCamera = 0;
	m_ColorShader = 0;
	m_TextureShader = 0;
	m_LightShader = 0;
	m_MeshShader = 0;
	m_MeshShaderColor = 0;
	m_FrameInformation.rotation = 0.0f;
}

GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}

GraphicsClass::~GraphicsClass()
{
}

bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd, InputClass* input)
{
	bool result;

    m_windowInfo = new WindowInfo(hwnd, screenWidth, screenHeight);
	m_Input = input;

	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd,
        FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, "Could not initialize Direct3D", "Error", MB_OK);
		return false;
	}

	// Create the user actions object.
	m_UserActions = new UserActions(m_Input);
	if (!m_UserActions)
	{
		return false;
	}

	// Initialize keyActionMapping pair by binding action and input key
	m_UserActions->Initialize();

	// Create the user camera object.
	m_UserCamera = new UserCamera(m_UserActions, FreeFly);
	if (!m_UserCamera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_UserCamera->SetPosition(0.0f, 0.0f, -10.0f);
	m_UserCamera->Render();

	// Initialize shaders
	result = InitializeColorShader();
	result = result && InitializeTextureShader();
	result = result && InitializeLightShader();
	result = result && InitializeMeshShader();
	result = result && InitializeMeshShaderColor();
	if (!result)
	{
		return false;
	}

    #if DirectXTK
	// Create Scene 2D object
	m_Scene2D = new Scene2DClass;
	if (!m_Scene2D)
	{
		return false;
	}

	// Initialize the Scene 2D object.
	result = m_Scene2D->Initialize(m_D3D, m_windowInfo);
	if (!result)
	{
		MessageBox(hwnd, "Could not initialize Scene2D", "Error", MB_OK);
		return false;
	}
    #endif

    m_Scene2DTest = new Scene2DClassTest;
	if (!m_Scene2DTest)
	{
		return false;
	}

	// Initialize the Scene 2D object.
	result = m_Scene2DTest->Initialize(m_D3D, m_windowInfo, m_TextureShader);
	if (!result)
	{
		MessageBox(hwnd, "Could not initialize Scene2DTest", "Error", MB_OK);
		return false;
	}

	// Create Scene 3D object
	m_Scene3D = new Scene3DClass;
	if (!m_Scene3D)
	{
		return false;
	}

	// Initialize the Scene 3D object.
	result = m_Scene3D->Initialize(m_D3D, hwnd, m_ColorShader, m_TextureShader, m_LightShader, m_MeshShader,
        m_MeshShaderColor);
	if (!result)
	{
		MessageBox(hwnd, "Could not initialize Scene3D", "Error", MB_OK);
		return false;
	}

	return result;
}

bool GraphicsClass::InitializeColorShader()
{
    bool result;

    // Create the color shader object.
	m_ColorShader = new ColorShaderClass;
	if(!m_ColorShader)
	{
		return false;
	}

	// Initialize the color shader object.
	result = m_ColorShader->Initialize(m_D3D->GetDevice(), m_windowInfo->m_hwnd);
	if(!result)
	{
		MessageBox(m_windowInfo->m_hwnd, "Could not initialize the color shader object.", "Error", MB_OK);
		return false;
	}

	return true;
}

bool GraphicsClass::InitializeTextureShader()
{
    bool result;

	// Create the texture shader object.
	m_TextureShader = new TextureShaderClass;
	if(!m_TextureShader)
	{
		return false;
	}

	// Initialize the texture shader object.
	result = m_TextureShader->Initialize(m_D3D->GetDevice(), m_windowInfo->m_hwnd);
	if(!result)
	{
		MessageBox(m_windowInfo->m_hwnd, "Could not initialize the texture shader object.", "Error", MB_OK);
		return false;
	}

	return true;
}

bool GraphicsClass::InitializeLightShader()
{
    bool result;

    // Create the light shader object.
	m_LightShader = new LightShaderClass;
	if(!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_D3D->GetDevice(), m_windowInfo->m_hwnd);
	if(!result)
	{
		MessageBox(m_windowInfo->m_hwnd, "Could not initialize the light shader object.", "Error", MB_OK);
		return false;
	}

	return true;
}

bool GraphicsClass::InitializeMeshShader()
{
	bool result;

	// Create the mesh shader object.
	m_MeshShader = new MeshShaderClass;
	if (!m_MeshShader)
	{
		return false;
	}

	// Initialize the mesh shader object.
	result = m_MeshShader->Initialize(m_D3D->GetDevice(), m_windowInfo->m_hwnd);
	if (!result)
	{
		MessageBox(m_windowInfo->m_hwnd, "Could not initialize the mesh shader object.", "Error", MB_OK);
		return false;
	}

	return true;
}

bool GraphicsClass::InitializeMeshShaderColor()
{
	bool result;

	// Create the mesh shader color object.
	m_MeshShaderColor = new MeshShaderColor;
	if (!m_MeshShaderColor)
	{
		return false;
	}

	// Initialize the mesh shader color object.
	result = m_MeshShaderColor->Initialize(m_D3D->GetDevice(), m_windowInfo->m_hwnd);
	if (!result)
	{
		MessageBox(m_windowInfo->m_hwnd, "Could not initialize the mesh shader color object.", "Error", MB_OK);
		return false;
	}

	return true;
}

void GraphicsClass::Shutdown()
{
	// Release the light shader object.
	if(m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}

	// Release the mesh shader object.
	if (m_MeshShader)
	{
		m_MeshShader->Shutdown();
		delete m_MeshShader;
		m_MeshShader = 0;
	}

    // Release the mesh shader color object.
	if (m_MeshShaderColor)
	{
		m_MeshShaderColor->Shutdown();
		delete m_MeshShaderColor;
		m_MeshShaderColor = 0;
	}

    // Release the texture shader object.
	if(m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

    // Release the color shader object.
	if(m_ColorShader)
	{
		m_ColorShader->Shutdown();
		delete m_ColorShader;
		m_ColorShader = 0;
	}

	// Release the user action object.
	if (m_UserActions)
	{
		delete m_UserActions;
		m_UserActions = 0;
	}

	// Release the user camera object.
	if(m_UserCamera)
	{
		delete m_UserCamera;
		m_UserCamera = 0;
	}

    #if DirectXTK
	// Release the scene 2D object.
	if (m_Scene2D)
	{
		delete m_Scene2D;
		m_Scene2D = 0;
	}
	#endif

    if (m_Scene2DTest)
	{
		delete m_Scene2DTest;
		m_Scene2DTest = 0;
	}

	// Release the scene 3D object.
	if (m_Scene3D)
	{
		delete m_Scene3D;
		m_Scene3D = 0;
	}

    // Release the Direct3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	// Release the WindowInfo object.
	if(m_windowInfo)
	{
		delete m_windowInfo;
		m_windowInfo = 0;
	}

	return;
}

bool GraphicsClass::Frame()
{
    bool result;

	// Update the rotation variable each frame.
	ComputeRotationInFrame();

	// Render the graphics scene.
	result = Render();
	if(!result)
	{
		return false;
	}

	return true;
}

bool GraphicsClass::Render()
{
	bool result;
	D3DXMATRIX viewMatrix;

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Update user camera
	m_UserCamera->Update();

	m_UserCamera->Render();

	// Generate the view matrix based on the camera's position.
	m_UserCamera->GetViewMatrix(viewMatrix);
	m_FrameInformation.userCameraPosition = m_UserCamera->GetPosition();

	m_Scene3D->Update(m_FrameInformation, viewMatrix);

    #if DirectXTK
	m_Scene2D->Update();
	#endif

	m_Scene2DTest->Update(m_FrameInformation);

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}

void GraphicsClass::ComputeRotationInFrame()
{
	m_FrameInformation.rotation += (float)D3DX_PI * 0.01f;
	if (m_FrameInformation.rotation > 360.0f)
	{
		m_FrameInformation.rotation -= 360.0f;
	}
}
