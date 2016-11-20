#ifndef D3DCLASS_H
#define D3DCLASS_H

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")
#pragma comment (lib, "D3D10_1.lib")
#pragma comment (lib, "D2D1.lib")
#pragma comment (lib, "dwrite.lib")

#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <xnamath.h>
#include <D3D10_1.h>
#include <D2D1.h>
#include <sstream>
#include <dwrite.h>

class D3DClass
{
private:
    struct Vertex
    {
        Vertex(){}
        Vertex(float x, float y, float z,
            float u, float v)
            : pos(x,y,z), texCoord(u, v){}

        XMFLOAT3 pos;
        XMFLOAT2 texCoord;
    };

    struct cbPerObject
    {
        XMMATRIX WVP;
    };

    cbPerObject cbPerObj;

public:
	D3DClass();
	D3DClass(const D3DClass&);
	~D3DClass();

	bool Initialize(int, int, bool, HWND, bool, float, float);
	void Shutdown();

	void BeginScene(float, float, float, float);
	void EndScene();

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();

	void GetProjectionMatrix(D3DXMATRIX&);
	void GetWorldMatrix(D3DXMATRIX&);
	void GetOrthoMatrix(D3DXMATRIX&);

	void GetVideoCardInfo(char*, int&);

	void TurnZBufferOn();
	void TurnZBufferOff();

	void TurnOnAlphaBlending();
	void TurnOffAlphaBlending();

	bool InitD2D_D3D101_DWrite(IDXGIAdapter1 *Adapter, int, int);
    void InitD2DScreenTexture();
    void RenderText(LPCSTR text, int, int);

private:
	bool m_vsync_enabled;
	int m_videoCardMemory;
	char m_videoCardDescription[128];
	IDXGISwapChain* m_swapChain;
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;
	ID3D11RenderTargetView* m_renderTargetView;
	ID3D11Texture2D* m_depthStencilBuffer;
	ID3D11DepthStencilState* m_depthStencilState;
	ID3D11DepthStencilView* m_depthStencilView;
	ID3D11RasterizerState* m_rasterState;

	D3DXMATRIX m_projectionMatrix;
	D3DXMATRIX m_worldMatrix;
	D3DXMATRIX m_orthoMatrix;

	ID3D11DepthStencilState* m_depthDisabledStencilState;

	ID3D11BlendState* m_alphaEnableBlendingState;
	ID3D11BlendState* m_alphaDisableBlendingState;


	ID3D10Device1 *d3d101Device;
    IDXGIKeyedMutex *keyedMutex11;
    IDXGIKeyedMutex *keyedMutex10;
    ID2D1RenderTarget *D2DRenderTarget;
    ID2D1SolidColorBrush *Brush;
    ID3D11Texture2D *BackBuffer11;//it repeats, I think, with m_depthStencilState
    ID3D11Texture2D *sharedTex11;
    ID3D11Buffer *d2dVertBuffer;
    ID3D11Buffer *d2dIndexBuffer;
    ID3D11ShaderResourceView *d2dTexture;
    IDWriteFactory *DWriteFactory;
    IDWriteTextFormat *TextFormat;
    LPCSTR printText;
};

#endif // D3DCLASS_H
