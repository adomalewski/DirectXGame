#ifndef MODELCLASS_H
#define MODELCLASS_H

#include <d3d11.h>
#include <d3dx10math.h>

#include "textureclass.h"

class ModelClass
{
private:
    struct VertexType_Color
	{
		D3DXVECTOR3 position;
		D3DXVECTOR4 color;
	};

	struct VertexType_Texture
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
	};

	struct VertexType_TextureNormal
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
		D3DXVECTOR3 normal;
	};

    typedef VertexType_TextureNormal VertexType;

public:
	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();

	bool Initialize4VertexColor(ID3D11Device*);
	bool Initialize4Texture(ID3D11Device*, LPCSTR);
	bool Initialize4TextureNormal(ID3D11Device*, LPCSTR);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();

	ID3D11ShaderResourceView* GetTexture();

private:
	bool InitializeBuffers4VertexColor(ID3D11Device*);
	bool InitializeBuffers4Texture(ID3D11Device*);
	bool InitializeBuffers4TextureNormal(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadTexture(ID3D11Device*, LPCSTR);
	void ReleaseTexture();

private:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;

	TextureClass* m_Texture;
};

#endif // MODELCLASS_H
