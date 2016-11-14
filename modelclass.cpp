#include "modelclass.h"

template <typename VertexType>
ModelClass<VertexType>::ModelClass()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
}

template <typename VertexType>
ModelClass<VertexType>::ModelClass(const ModelClass& other)
{
}

template <typename VertexType>
ModelClass<VertexType>::~ModelClass()
{
}

template <typename VertexType>
void ModelClass<VertexType>::Shutdown()
{
	// Release the vertex and index buffers.
	ShutdownBuffers();

	return;
}

template <typename VertexType>
void ModelClass<VertexType>::Render(ID3D11DeviceContext* deviceContext)
{
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(deviceContext);

	return;
}

template <typename VertexType>
int ModelClass<VertexType>::GetIndexCount()
{
	return m_indexCount;
}

template <typename VertexType>
void ModelClass<VertexType>::ShutdownBuffers()
{
	// Release the index buffer.
	if(m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	// Release the vertex buffer.
	if(m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	return;
}

template <typename VertexType>
void ModelClass<VertexType>::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;

	// Set vertex buffer stride and offset.
	stride = sizeof(VertexType);
	offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}

template class ModelClass<VertexTypeColor>;
template class ModelClass<VertexTypeTexture>;
template class ModelClass<VertexTypeTextureNormal>;
