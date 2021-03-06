#ifndef FONTSHADERCLASS_H
#define FONTSHADERCLASS_H

#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>
#include <fstream>
using namespace std;

class FontShaderClass
{
private:
	struct PixelBufferType
	{
		D3DXVECTOR4 pixelColor;
	};

public:
	FontShaderClass();
	FontShaderClass(const FontShaderClass&);
	~FontShaderClass();

	bool Initialize(ID3D11Device*);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, int, ID3D11ShaderResourceView*, D3DXVECTOR4);

private:
	bool InitializeShader(ID3D11Device*, LPCSTR, LPCSTR);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, LPCSTR);

	bool SetShaderParameters(ID3D11DeviceContext*, ID3D11ShaderResourceView*, D3DXVECTOR4);
	void RenderShader(ID3D11DeviceContext*, int);

private:
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11SamplerState* m_sampleState;
	ID3D11Buffer* m_pixelBuffer;
};

#endif // FONTSHADERCLASS_H
