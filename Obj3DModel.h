#pragma once

#include <vector>
#include <fstream>
#include <sstream>

#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11tex.h>

struct cbPerObject
{
	D3DXMATRIX  WVP;
	D3DXMATRIX World;

	///////////////**************new**************////////////////////
	//These will be used for the pixel shader
	D3DXVECTOR4 difColor;
	bool hasTexture;
	///////////////**************new**************////////////////////
};

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

	bool LoadObjModel(ID3D11Device*, LPCSTR, ID3D11Buffer**, ID3D11Buffer**,
		std::vector<int>&, std::vector<int>&, std::vector<SurfaceMaterial>&,
		int&, bool, bool);

	void Shutdown();

private:
	ID3D11BlendState* Transparency;

	ID3D11Buffer* meshVertBuff;
	ID3D11Buffer* meshIndexBuff;
	D3DXMATRIX meshWorld;
	int meshSubsets = 0;
	std::vector<int> meshSubsetIndexStart;
	std::vector<int> meshSubsetTexture;

	std::vector<ID3D11ShaderResourceView*> meshSRV;
	std::vector<std::string> textureNameArray;

	std::vector<SurfaceMaterial> material;
};

