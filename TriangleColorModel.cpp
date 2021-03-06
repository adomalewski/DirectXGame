#include "TriangleColorModel.h"

TriangleColorModel::TriangleColorModel()
{
}

TriangleColorModel::TriangleColorModel(const TriangleColorModel& other)
{
}

TriangleColorModel::~TriangleColorModel()
{
}

bool TriangleColorModel::Initialize(ID3D11Device* device)
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

ColorModel::ModelDataType TriangleColorModel::CreateModelData()
{
    VertexTypeColor* vertices;
    unsigned long* indices;

	int vertexCount = 3;
	int indexCount = 3;

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
	vertices[0].position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);  // Bottom left.
	vertices[0].color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);

	vertices[1].position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);  // Top middle.
	vertices[1].color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);

	vertices[2].position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);  // Bottom right.
	vertices[2].color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);

	// Load the index array with data.
	indices[0] = 0;  // Bottom left.
	indices[1] = 1;  // Top middle.
	indices[2] = 2;  // Bottom right.

	return boost::make_tuple(boost::ref(vertices), boost::ref(indices), vertexCount, indexCount);
}
