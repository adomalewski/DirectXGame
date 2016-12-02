#include "SimpleSurface.h"

SimpleSurface::SimpleSurface()
{
    m_TextureNormalModel = 0;
}

SimpleSurface::SimpleSurface(const SimpleSurface& other)
{
}

SimpleSurface::~SimpleSurface()
{
}

bool SimpleSurface::Initialize(ID3D11Device* device)
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

ModelDataType SimpleSurface::CreateModelData()
{
    VertexTypeTextureNormal* vertices;
    unsigned long* indices;

	int lineAmount = 4;

	int vertexCount = 6 * lineAmount * lineAmount;
	int indexCount = vertexCount;

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

	for (int i = 0, actIndex = 0; i < lineAmount; ++i) //y
	{
		for (int j = 0; j < lineAmount; ++j) //x
		{
			vertices[actIndex].position = D3DXVECTOR3(j, i, 0.0f);  // Bottom left.
			vertices[actIndex].texture = D3DXVECTOR2(0.0f, 0.0f);
			vertices[actIndex].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			indices[actIndex] = actIndex;

			++actIndex;;
			vertices[actIndex].position = D3DXVECTOR3(j, i+1, 0.0f);  // Top left.
			vertices[actIndex].texture = D3DXVECTOR2(0.5f, 0.0f);
			vertices[actIndex].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			indices[actIndex] = actIndex;

			++actIndex;
			vertices[actIndex].position = D3DXVECTOR3(j+1, i, 0.0f);  // Bottom right.
			vertices[actIndex].texture = D3DXVECTOR2(1.0f, 1.0f);
			vertices[actIndex].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			indices[actIndex] = actIndex;

			++actIndex;
			vertices[actIndex].position = D3DXVECTOR3(j+1, i, 0.0f);  // Bottom left.
			vertices[actIndex].texture = D3DXVECTOR2(0.0f, 1.0f);
			vertices[actIndex].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			indices[actIndex] = actIndex;

			++actIndex;
			vertices[actIndex].position = D3DXVECTOR3(j, i+1, 0.0f);  // Top left.
			vertices[actIndex].texture = D3DXVECTOR2(0.5f, 0.0f);
			vertices[actIndex].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			indices[actIndex] = actIndex;

			++actIndex;
			vertices[actIndex].position = D3DXVECTOR3(j+1, i+1, 0.0f);  // Bottom right.
			vertices[actIndex].texture = D3DXVECTOR2(1.0f, 1.0f);
			vertices[actIndex].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			indices[actIndex] = actIndex;

			++actIndex;
		}
	}

	D3DXMATRIX finalMat, translMat, rotMat;

	D3DXMatrixTranslation(&translMat, -0.5*lineAmount, -0.5*lineAmount, 0);
	D3DXMatrixRotationX(&rotMat, D3DX_PI / 2);
	finalMat = translMat * rotMat;
	D3DXMatrixTranslation(&translMat, 0, -2.5f, 0);
	finalMat *= translMat;

	D3DXVec3TransformCoord(&vertices[0].normal, &vertices[0].normal, &finalMat);
	D3DXVec3Normalize(&vertices[0].normal, &vertices[0].normal);
	
	for (int i = 0; i < vertexCount; ++i)
	{
		D3DXVec3TransformCoord(&vertices[i].position, &vertices[i].position, &finalMat);
		vertices[i].normal = vertices[0].normal;
	}

	return boost::make_tuple(boost::ref(vertices), boost::ref(indices), vertexCount, indexCount);
}

void SimpleSurface::ReleaseModelData(VertexTypeTextureNormal* vertices, unsigned long* indices)
{
    delete [] vertices;
	vertices = 0;

	delete [] indices;
	indices = 0;
}

void SimpleSurface::Shutdown()
{
	// Release the model object.
	if (m_TextureNormalModel)
	{
		m_TextureNormalModel->Shutdown();
		delete m_TextureNormalModel;
		m_TextureNormalModel = 0;
	}
}

bool SimpleSurface::Render(ID3D11DeviceContext* deviceContext, LightShaderClass* lightShader,
    D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix, D3DXVECTOR3 lightDirection,
    D3DXVECTOR4 diffuseColor)
{
    bool result;

    m_TextureNormalModel->Render(deviceContext);
    result = lightShader->Render(deviceContext, m_TextureNormalModel->GetIndexCount(), worldMatrix,
        viewMatrix, projectionMatrix, m_TextureNormalModel->GetTexture(), lightDirection, diffuseColor);

    return result;
}
