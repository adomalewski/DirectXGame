#include "DrawLine3DSpace.h"

DrawLine3DSpace::DrawLine3DSpace()
{
}

DrawLine3DSpace::DrawLine3DSpace(const DrawLine3DSpace& other)
{
}

DrawLine3DSpace::~DrawLine3DSpace()
{
}

bool DrawLine3DSpace::Initialize(ID3D11Device* device)
{
    bool result = true;
    ModelDataType modelDataType;

	modelDataType = CreateModelData();
	if (!modelDataType.get<0>() || !modelDataType.get<1>())
	{
        return false;
	}

	result = ColorModel::Initialize(device, modelDataType.get<0>(), modelDataType.get<1>(),
        modelDataType.get<2>(), modelDataType.get<3>());

	ReleaseModelData(modelDataType.get<0>(), modelDataType.get<1>());

    return result;
}

ColorModel::ModelDataType DrawLine3DSpace::CreateModelData()
{
    VertexTypeColor* vertices;
    unsigned long* indices;

	int vertexCount = 2;
	int indexCount = 2;

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

    // Load the vertex array with data.
	vertices[0].position = D3DXVECTOR3(0.0f, -2.0f, 0.0f);
	vertices[0].color = D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f);

	vertices[1].position = D3DXVECTOR3(1.0f, 5.0f, 3.0f);
	vertices[1].color = D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f);

	// Load the index array with data.
	indices[0] = 0;  // Bottom left.
	indices[1] = 1;  // Top middle.

	return boost::make_tuple(boost::ref(vertices), boost::ref(indices), vertexCount, indexCount);
}

bool DrawLine3DSpace::Render(ID3D11DeviceContext* deviceContext, ColorShaderClass* colorShader, D3DXMATRIX worldMatrix,
			      D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix)
{
    return ColorModel::Render(deviceContext, colorShader, worldMatrix, viewMatrix, projectionMatrix,
        D3D_PRIMITIVE_TOPOLOGY_LINELIST);
}
