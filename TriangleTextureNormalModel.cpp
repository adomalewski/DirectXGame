#include "TriangleTextureNormalModel.h"

TriangleTextureNormalModel::TriangleTextureNormalModel()
{
    m_TextureNormalModel = 0;
}

TriangleTextureNormalModel::TriangleTextureNormalModel(const TriangleTextureNormalModel& other)
{
}

TriangleTextureNormalModel::~TriangleTextureNormalModel()
{
}

bool TriangleTextureNormalModel::Initialize(ID3D11Device* device)
{
    bool result = true;
    ModelDataType modelDataType;

    m_TextureNormalModel = new TextureNormalModel;
	if (!m_TextureNormalModel)
	{
		return false;
	}

	modelDataType = CreateModelData();
	if (!modelDataType.get<0>() || !modelDataType.get<1>())
	{
        return false;
	}

	result = m_TextureNormalModel->Initialize(device, "Stonehenge.jpg", modelDataType.get<0>(), modelDataType.get<1>(),
        modelDataType.get<2>(), modelDataType.get<3>());

	ReleaseModelData(modelDataType.get<0>(), modelDataType.get<1>());

    return result;
}

ModelDataType TriangleTextureNormalModel::CreateModelData()
{
    VertexTypeTextureNormal* vertices;
    unsigned long* indices;

	int vertexCount = 6;
	int indexCount = 6;

	// Create the vertex array.
	vertices = new VertexTypeTextureNormal[vertexCount];
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
	vertices[0].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	vertices[1].position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);  // Top middle.
	vertices[1].texture = D3DXVECTOR2(0.5f, 0.0f);
	vertices[1].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	vertices[2].position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);  // Bottom right.
	vertices[2].texture = D3DXVECTOR2(1.0f, 1.0f);
	vertices[2].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	vertices[3].position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);  // Bottom right.
	vertices[3].texture = D3DXVECTOR2(0.0f, 1.0f);
	vertices[3].normal = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	vertices[4].position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);  // Top middle.
	vertices[4].texture = D3DXVECTOR2(0.5f, 0.0f);
	vertices[4].normal = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	vertices[5].position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);  // Bottom left.
	vertices[5].texture = D3DXVECTOR2(1.0f, 1.0f);
	vertices[5].normal = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	// Load the index array with data.
	indices[0] = 0;  // Bottom left.
	indices[1] = 1;  // Top middle.
	indices[2] = 2;  // Bottom right.

	indices[3] = 3;  // Bottom left.
	indices[4] = 4;  // Top middle.
	indices[5] = 5;  // Bottom right.

	return boost::make_tuple(boost::ref(vertices), boost::ref(indices), vertexCount, indexCount);
}

void TriangleTextureNormalModel::ReleaseModelData(VertexTypeTextureNormal* vertices, unsigned long* indices)
{
    delete [] vertices;
	vertices = 0;

	delete [] indices;
	indices = 0;
}

void TriangleTextureNormalModel::Shutdown()
{
	// Release the model object.
	if (m_TextureNormalModel)
	{
		m_TextureNormalModel->Shutdown();
		delete m_TextureNormalModel;
		m_TextureNormalModel = 0;
	}
}

bool TriangleTextureNormalModel::Render(ID3D11DeviceContext* deviceContext, LightShaderClass* lightShader,
    D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix, D3DXVECTOR3 lightDirection,
    D3DXVECTOR4 ambientColor, D3DXVECTOR4 diffuseColor, D3DXVECTOR3 cameraPosition,
    D3DXVECTOR4 specularColor, float specularPower)
{
    bool result;

    m_TextureNormalModel->Render(deviceContext);
    result = lightShader->Render(deviceContext, m_TextureNormalModel->GetIndexCount(), worldMatrix,
        viewMatrix, projectionMatrix, m_TextureNormalModel->GetTexture(), lightDirection,
        ambientColor, diffuseColor, cameraPosition, specularColor, specularPower);

    return result;
}
