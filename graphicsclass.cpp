#include "graphicsclass.h"

GraphicsClass::GraphicsClass()
{
    m_D3D = 0;
    m_Camera = 0;
	m_ColorShader = 0;
	m_TextureShader = 0;
	m_LightShader = 0;
	m_FrameInformation.rotation = 0.0f;
}

GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}

GraphicsClass::~GraphicsClass()
{
}

bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;
	D3DXMATRIX viewMatrix;

	m_hwnd = hwnd;

	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, m_hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(m_hwnd, "Could not initialize Direct3D", "Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);
	m_Camera->Render();
	m_Camera->GetViewMatrix(viewMatrix);

	// Initialize shaders
	result = InitializeColorShader();
	result = result && InitializeTextureShader();
	result = result && InitializeLightShader();
	if (!result)
	{
		return false;
	}

	// Create Scene 2D object
	m_Scene2D = new Scene2DClass;
	if (!m_Scene2D)
	{
		return false;
	}

	// Initialize the Scene 2D object.
	result = m_Scene2D->Initialize(m_D3D, m_hwnd, screenWidth, screenHeight, m_TextureShader, viewMatrix);
	if (!result)
	{
		MessageBox(m_hwnd, "Could not initialize Scene2D", "Error", MB_OK);
		return false;
	}

	// Create Scene 3D object
	m_Scene3D = new Scene3DClass;
	if (!m_Scene3D)
	{
		return false;
	}

	// Initialize the Scene 3D object.
	result = m_Scene3D->Initialize(m_D3D, m_hwnd, viewMatrix, m_ColorShader, m_TextureShader, m_LightShader);
	if (!result)
	{
		MessageBox(m_hwnd, "Could not initialize Scene3D", "Error", MB_OK);
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
	result = m_ColorShader->Initialize(m_D3D->GetDevice(), m_hwnd);
	if(!result)
	{
		MessageBox(m_hwnd, "Could not initialize the color shader object.", "Error", MB_OK);
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
	result = m_TextureShader->Initialize(m_D3D->GetDevice(), m_hwnd);
	if(!result)
	{
		MessageBox(m_hwnd, "Could not initialize the texture shader object.", "Error", MB_OK);
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
	result = m_LightShader->Initialize(m_D3D->GetDevice(), m_hwnd);
	if(!result)
	{
		MessageBox(m_hwnd, "Could not initialize the light shader object.", "Error", MB_OK);
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

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

    // Release the Direct3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
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

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	m_Scene3D->Update(m_FrameInformation);

	m_Scene2D->Update();

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
