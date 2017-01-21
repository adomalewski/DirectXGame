#ifndef FONTCLASS_H
#define FONTCLASS_H

#include <d3d11.h>
#include <d3dx10math.h>
#include <fstream>
#include <string>

#include "textureclass.h"
#include "WindowInfo.h"

using namespace std;

class FontClass
{
private:
	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
	};

	struct FontChar
    {
        // the unicode id
        int id;

        // these need to be converted to texture coordinates
        // (where 0.0 is 0 and 1.0 is textureWidth of the font)
        float u; // u texture coordinate
        float v; // v texture coordinate
        float twidth; // width of character on texture
        float theight; // height of character on texture

        float width; // width of character in screen coords
        float height; // height of character in screen coords

        // these need to be normalized based on size of font
        float xoffset; // offset from current cursor pos to left side of character
        float yoffset; // offset from top of line to top of character
        float xadvance; // how far to move to right for next character
    };

    struct FontKerning
    {
        int firstid; // the first character
        int secondid; // the second character
        float amount; // the amount to add/subtract to second characters x
    };

    struct FontData
    {
        std::string name; // name of the font
        std::string fontImage;
        int size; // size of font, lineheight and baseheight will be based on this as if this is a single unit (1.0)
        float lineHeight; // how far to move down to next line, will be normalized
        float baseHeight; // height of all characters, will be normalized
        int textureWidth; // width of the font texture
        int textureHeight; // height of the font texture
        int numCharacters; // number of characters in the font
        FontChar* CharList; // list of characters
        int numKernings; // the number of kernings
        FontKerning* KerningsList; // list to hold kerning values

        // these are how much the character is padded in the texture. We
        // add padding to give sampling a little space so it does not accidentally
        // padd the surrounding characters. We will need to subtract these paddings
        // from the actual spacing between characters to remove the gaps you would otherwise see
        float leftpadding;
        float toppadding;
        float rightpadding;
        float bottompadding;

        // this will return the amount of kerning we need to use for two characters
        float GetKerning(char first, char second)
        {
            for (int i = 0; i < numKernings; ++i)
            {
                if ((char)KerningsList[i].firstid == first && (char)KerningsList[i].secondid == second)
                    return KerningsList[i].amount;
            }
            return 0.0f;
        }

        FontChar* GetChar(char c)
        {
            for (int i = 0; i < numCharacters; ++i)
            {
                if (c == (char)CharList[i].id)
                    return &CharList[i];
            }
            return nullptr;
        }
    };

public:
	FontClass();
	FontClass(const FontClass&);
	~FontClass();

	bool Initialize(ID3D11Device*, WindowInfo*, std::string);
	void Shutdown();

	ID3D11ShaderResourceView* GetTexture();

	void BuildVertexArray(void*, char*, float, float);

private:
    bool LoadFontData(LPCSTR);
	void ReleaseFontData();
	bool LoadTexture(ID3D11Device*, LPCSTR);
	void ReleaseTexture();

private:
    WindowInfo* m_windowInfo;
    FontData m_FontData;
	TextureClass* m_Texture;
};

#endif // FONTCLASS_H
