#include "TriangleTextureModel.h"

TriangleTextureModel::TriangleTextureModel()
{
    m_TextureModel = 0;
}

TriangleTextureModel::TriangleTextureModel(const TriangleTextureModel& other)
{
}

TriangleTextureModel::~TriangleTextureModel()
{
}

bool TriangleTextureModel::Initialize(ID3D11Device* device)
{
    bool result = true;
    ModelDataType modelDataType;

    m_TextureModel = new TextureModel<VertexTypeTexture>;
	if (!m_TextureModel)
	{
		return false;
	}

	modelDataType = CreateModelData();
	if (!modelDataType.get<0>() || !modelDataType.get<1>())
	{
        return false;
	}

	result = m_TextureModel->Initialize(device, "Stonehenge.jpg", modelDataType.get<0>(), modelDataType.get<1>(),
        modelDataType.get<2>(), modelDataType.get<3>());

	ReleaseModelData(modelDataType.get<0>(), modelDataType.get<1>());

    return result;
}

TriangleTextureModel::ModelDataType TriangleTextureModel::CreateModelData()
{
    VertexTypeTexture* vertices;
    unsigned long* indices;

	int vertexCount = 3;
	int indexCount = 3;

	// Create the vertex array.
	vertices = new VertexTypeTexture[vertexCount];
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

    // Load the vertex array with data.
	vertices[0].position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);  // Bottom left.
	vertices[0].texture = D3DXVECTOR2(0.0f, 1.0f);

	vertices[1].position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);  // Top middle.
	vertices[1].texture = D3DXVECTOR2(0.5f, 0.0f);

	vertices[2].position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);  // Bottom right.
	vertices[2].texture = D3DXVECTOR2(1.0f, 1.0f);

	// Load the index array with data.
	indices[0] = 0;  // Bottom left.
	indices[1] = 1;  // Top middle.
	indices[2] = 2;  // Bottom right.

	return boost::make_tuple(boost::ref(vertices), boost::ref(indices), vertexCount, indexCount);
}

void TriangleTextureModel::ReleaseModelData(VertexTypeTexture* vertices, unsigned long* indices)
{
    delete [] vertices;
	vertices = 0;

	delete [] indices;
	indices = 0;
}

void TriangleTextureModel::Shutdown()
{
	// Release the model object.
	if (m_TextureModel)
	{
		m_TextureModel->Shutdown();
		delete m_TextureModel;
		m_TextureModel = 0;
	}
}

bool TriangleTextureModel::Render(ID3D11DeviceContext* deviceContext, TextureShaderClass* textureShader,
    D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix)
{
    bool result;

    m_TextureModel->Render(deviceContext);
    result = textureShader->Render(deviceContext, m_TextureModel->GetIndexCount(), worldMatrix,
        viewMatrix, projectionMatrix, m_TextureModel->GetTexture());

    return result;
}
