#ifndef VERTEXTYPE_H
#define VERTEXTYPE_H

#include <d3d11.h>
#include <d3dx10math.h>

struct VertexTypeColor
{
    D3DXVECTOR3 position;
    D3DXVECTOR4 color;
};

struct VertexTypeTexture
{
    D3DXVECTOR3 position;
    D3DXVECTOR2 texture;
};

struct VertexTypeTextureNormal
{
    D3DXVECTOR3 position;
    D3DXVECTOR2 texture;
    D3DXVECTOR3 normal;
};

#endif // VERTEXTYPE_H
