#ifndef SCENE3DCLASS_H
#define SCENE3DCLASS_H

#include "d3dclass.h"
#include "modelclass.h"
#include "colorshaderclass.h"
#include "textureshaderclass.h"
#include "lightshaderclass.h"
#include "meshshaderclass.h"
#include "meshshadercolor.h"
#include "lightclass.h"
#include "FrameInformation.h"
#include "TriangleColorModel.h"
#include "TriangleTextureModel.h"
#include "TriangleTextureNormalModel.h"
#include "SimpleSurface.h"
#include "Obj3DModel.h"
#include "Axes3DSpace.h"

class Scene3DClass
{
public:
	Scene3DClass();
	~Scene3DClass();

	bool Initialize(D3DClass* m_D3D, HWND hwnd, ColorShaderClass*,
        TextureShaderClass*, LightShaderClass*, MeshShaderClass*, MeshShaderColor*);
	void Shutdown();

	void Update(FrameInformation, D3DXMATRIX);

	void ComputeScreenWorld(D3DXMATRIX&, D3DXMATRIX&, D3DXMATRIX&, float, float);

private:
	D3DClass* m_D3D;
	HWND m_hwnd;
	ModelBase* m_ModelList;
	TriangleColorModel* m_TriangleColorModel;
	TriangleTextureModel* m_TriangleTextureModel;
	TriangleTextureNormalModel* m_TriangleTextureNormalModel;
	ColorShaderClass* m_ColorShader;
	TextureShaderClass* m_TextureShader;
	LightShaderClass* m_LightShader;
	MeshShaderClass* m_MeshShader;
	MeshShaderColor* m_MeshShaderColor;
	LightClass* m_Light;
	SimpleSurface* m_SimpleSurface;
	Obj3DModel* m_AppartmentModel;
	Axes3DSpace* m_Axes3D;
	Obj3DModel* m_Axes3DArrows;
};

#endif // SCENE3DCLASS_H
