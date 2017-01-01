#ifndef MESHSHADERCOLOR_H
#define MESHSHADERCOLOR_H

#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>
#include <fstream>
using namespace std;

class MeshShaderColor
{
private:
	struct MatrixBufferType
	{
		D3DXMATRIX world;
		D3DXMATRIX view;
		D3DXMATRIX projection;
	};

	struct MeshBufferType
	{
		D3DXVECTOR4 difColor;
		bool hasTexture;
		D3DXVECTOR3 padding;
	};

public:
	MeshShaderColor();
	MeshShaderColor(const MeshShaderColor&);
	~MeshShaderColor();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, int, int, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX,
        ID3D11ShaderResourceView*, D3DXVECTOR4, bool);

private:
	bool InitializeShader(ID3D11Device*, HWND, LPCSTR, LPCSTR);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, LPCSTR);

	bool SetShaderParameters(ID3D11DeviceContext*, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX,
        ID3D11ShaderResourceView*, D3DXVECTOR4, bool);
	void RenderShader(ID3D11DeviceContext*, int, int);

private:
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11SamplerState* m_sampleState;
	ID3D11Buffer* m_matrixBuffer;
	ID3D11Buffer* m_meshBuffer;

	ID3D11RasterizerState* RSCullNone;
};

#endif // MESHSHADERCOLOR_H
