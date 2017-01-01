#include "Axes3DSpace.h"

Axes3DSpace::Axes3DSpace()
{
    m_DrawLine3D = 0;
}

Axes3DSpace::~Axes3DSpace()
{
}

bool Axes3DSpace::Initialize(ID3D11Device* device)
{
    bool result = true;
    ColorModel::ModelDataType modelData;

	modelData = CreateModelData();
	if (!modelData.get<0>() || !modelData.get<1>())
	{
        return false;
	}

    m_DrawLine3D = new DrawLine3DSpace;
	if (!m_DrawLine3D)
	{
		return false;
	}

	result = m_DrawLine3D->Initialize(device, modelData);

	m_DrawLine3D->ReleaseModelData(modelData.get<0>(), modelData.get<1>());

    return result;
}

ColorModel::ModelDataType Axes3DSpace::CreateModelData()
{
    VertexTypeColor* vertices;
    unsigned long* indices;

	int vertexCount = 6;
	int indexCount = 6;

	float axis_size = 1.0f;

	// Create the vertex array.
	vertices = new VertexTypeColor[vertexCount];
	if(!vertices)
	{
		return NULL;
	}

	// Create the index array.
	indices = new unsigned long[indexCount];
	if(!indices)
	{
		return NULL;
	}

    // X
	vertices[0].position = D3DXVECTOR3(-axis_size, 0.0f, 0.0f);
	vertices[0].color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);

	vertices[1].position = D3DXVECTOR3(axis_size, 0.0f, 0.0f);
	vertices[1].color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);

	// Y
    vertices[2].position = D3DXVECTOR3(0.0f, -axis_size, 0.0f);
	vertices[2].color = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);

	vertices[3].position = D3DXVECTOR3(0.0f, axis_size, 0.0f);
	vertices[3].color = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);

	// Z
    vertices[4].position = D3DXVECTOR3(0.0f, 0.0f, -axis_size);
	vertices[4].color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);

	vertices[5].position = D3DXVECTOR3(0.0f, 0.0f, axis_size);
	vertices[5].color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);

	// Load the index array with data.
	for(int i = 0; i < indexCount; ++i)
        indices[i] = i;

	return boost::make_tuple(boost::ref(vertices), boost::ref(indices), vertexCount, indexCount);
}

void Axes3DSpace::Shutdown()
{
	if (m_DrawLine3D)
	{
		m_DrawLine3D->Shutdown();
		delete m_DrawLine3D;
		m_DrawLine3D = 0;
	}
}

bool Axes3DSpace::Render(ID3D11DeviceContext* deviceContext, ColorShaderClass* colorShader, D3DXMATRIX worldMatrix,
			      D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix)
{
    return m_DrawLine3D->Render(deviceContext, colorShader, worldMatrix, viewMatrix, projectionMatrix);
}
