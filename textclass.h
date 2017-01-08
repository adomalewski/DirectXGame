#ifndef TEXTCLASS_H
#define TEXTCLASS_H

#include "WindowInfo.h"
#include "fontclass.h"
#include "fontshaderclass.h"

class TextClass
{
private:
	struct SentenceType
	{
		ID3D11Buffer *vertexBuffer, *indexBuffer;
		int vertexCount, indexCount, maxLength;
		D3DXVECTOR4 color;
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

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, WindowInfo*);
	void Shutdown();
	bool Render(ID3D11DeviceContext*);

private:
	bool InitializeSentence(SentenceType**, int, ID3D11Device*);
	bool UpdateSentence(SentenceType*, char*, int, int, float, float, float, ID3D11DeviceContext*);
	void ReleaseSentence(SentenceType**);
	bool RenderSentence(ID3D11DeviceContext*, SentenceType*);

private:
	FontClass* m_Font;
	FontShaderClass* m_FontShader;
	WindowInfo* m_windowInfo;
	SentenceType* m_sentence;
};

#endif // TEXTCLASS_H
