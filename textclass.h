#ifndef TEXTCLASS_H
#define TEXTCLASS_H

#include "fontclass.h"
#include "fontshaderclass.h"

class TextClass
{
private:
	struct SentenceType
	{
		ID3D11Buffer *vertexBuffer, *indexBuffer;
		int vertexCount, indexCount, maxLength;
		float red, green, blue;
	};

	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
	};

public:
	TextClass();
	TextClass(const TextClass&);
	~TextClass();

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, HWND, int, int, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX);
	void Shutdown();
	bool Render(ID3D11DeviceContext*);

	bool SetMousePosition(int, int, ID3D11DeviceContext*);

private:
	bool InitializeSentence(SentenceType**, int, ID3D11Device*);
	bool UpdateSentence(SentenceType*, char*, int, int, float, float, float, ID3D11DeviceContext*);
	void ReleaseSentence(SentenceType**);
	bool RenderSentence(ID3D11DeviceContext*, SentenceType*);

private:
	FontClass* m_Font;
	FontShaderClass* m_FontShader;
	int m_screenWidth, m_screenHeight;
	D3DXMATRIX m_staticViewMatrix;
	D3DXMATRIX m_staticWorldMatrix;
	D3DXMATRIX m_staticOrthoMatrix;
	SentenceType* m_sentence1;
	SentenceType* m_sentence2;
};

#endif // TEXTCLASS_H
