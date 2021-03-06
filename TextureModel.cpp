#include "TextureModel.h"

template <typename VertexType>
TextureModel<VertexType>::TextureModel()
{
	m_Texture = 0;
}

template <typename VertexType>
TextureModel<VertexType>::TextureModel(const TextureModel& other)
{
}

template <typename VertexType>
TextureModel<VertexType>::~TextureModel()
{
}

template <typename VertexType>
bool TextureModel<VertexType>::Initialize(ID3D11Device* device, LPCSTR textureFilename,
    VertexTypeTexture* vertices, unsigned long* indices, int vertexCount, int indexCount)
{
	bool result;

	// Initialize the vertex and index buffer that hold the geometry for the triangle.
	result = InitializeBuffers(device, vertices, indices, vertexCount, indexCount);
	if(!result)
	{
		return false;
	}

	// Load the texture for this model.
	result = LoadTexture(device, textureFilename);
	if(!result)
	{
		return false;
	}

	return true;
}

template <typename VertexType>
void TextureModel<VertexType>::Shutdown()
{
    // Release the model texture.
	ReleaseTexture();

	ModelClass::Shutdown();

	return;
}

template <typename VertexType>
ID3D11ShaderResourceView* TextureModel<VertexType>::GetTexture()
{
	return m_Texture->GetTexture();
}

template <typename VertexType>
bool TextureModel<VertexType>::InitializeBuffers(ID3D11Device* device, VertexTypeTexture* vertices,
    unsigned long* indices, int vertexCount, int indexCount)
{
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

    // Set the number of vertices in the vertex array.
	m_vertexCount = vertexCount;

	// Set the number of indices in the index array.
	m_indexCount = indexCount;

	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	return true;
}

template <typename VertexType>
bool TextureModel<VertexType>::LoadTexture(ID3D11Device* device, LPCSTR filename)
{
	bool result;

	// Create the texture object.
	m_Texture = new TextureClass;
	if(!m_Texture)
	{
		return false;
	}

	// Initialize the texture object.
	result = m_Texture->Initialize(device, filename);
	if(!result)
	{
		return false;
	}

	return true;
}

template <typename VertexType>
void TextureModel<VertexType>::ReleaseTexture()
{
	// Release the texture object.
	if(m_Texture)
	{
		m_Texture->Shutdown();
		delete m_Texture;
		m_Texture = 0;
	}

	return;
}

template class TextureModel<VertexTypeTexture>;
template class TextureModel<VertexTypeTextureNormal>;
