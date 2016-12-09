#pragma once

#include <vector>
#include <fstream>
#include <sstream>

#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11tex.h>

#include "d3dclass.h"
#include "TextureNormalModel.h"
#include "MeshShaderClass.h"

struct SurfaceMaterial
{
	std::string matName;
	D3DXVECTOR4 difColor;
	int texArrayIndex;
	bool hasTexture;
	bool transparent;
};

struct Vertex
{
	Vertex() {}
	Vertex(float x, float y, float z,
		float u, float v,
		float nx, float ny, float nz)
		: pos(x, y, z), texCoord(u, v), normal(nx, ny, nz) {}

	D3DXVECTOR3 pos;
	D3DXVECTOR2 texCoord;
	D3DXVECTOR3 normal;
};

class Obj3DModel
{
public:
	Obj3DModel();
	~Obj3DModel();

	bool Initialize(ID3D11Device* device,
        LPCSTR filename,
        bool isRHCoordSys = true,
        bool computeNormals = false);
	bool Render(ID3D11DeviceContext*, D3DClass*, MeshShaderClass*, D3DXMATRIX,
		D3DXMATRIX, D3DXMATRIX, D3DXVECTOR3, D3DXVECTOR4, D3DXVECTOR4, D3DXVECTOR3,
		D3DXVECTOR4, float);

	void Shutdown();

private:
	ID3D11Buffer* meshVertBuff;
	ID3D11Buffer* meshIndexBuff;
	D3DXMATRIX meshWorld;
	int meshSubsets;
	std::vector<int> meshSubsetIndexStart;
	std::vector<int> meshSubsetTexture;

	std::vector<ID3D11ShaderResourceView*> meshSRV;
	std::vector<std::string> textureNameArray;

	std::vector<SurfaceMaterial> material;

    TextureNormalModel* m_TextureNormalModel;
};

