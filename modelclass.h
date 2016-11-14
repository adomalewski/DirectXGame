#ifndef MODELCLASS_H
#define MODELCLASS_H

#include <d3d11.h>
#include <d3dx10math.h>

#include "textureclass.h"
#include "VertexType.h"

class ModelBase
{
};

template <typename VertexType>
class ModelClass : public ModelBase
{
public:
	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();

	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();

private:
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

protected:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
};

#endif // MODELCLASS_H
