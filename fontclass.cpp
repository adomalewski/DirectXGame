#include "fontclass.h"

FontClass::FontClass()
{
	m_Texture = 0;
}

FontClass::FontClass(const FontClass& other)
{
}

FontClass::~FontClass()
{
}

bool FontClass::Initialize(ID3D11Device* device, WindowInfo* windowInfo, std::string fontFilename)
{
	bool result;

	std::string fontPath = "font/";
	std::string fontFullPath = fontPath + fontFilename;

    m_windowInfo = windowInfo;

	// Load in the text file containing the font data.
	result = LoadFontData(fontFullPath.c_str());
	if (!result)
	{
		return false;
	}

	std::string fontImageFullPath = fontPath + m_FontData.fontImage;

	// Load the texture that has the font characters on it.
	result = LoadTexture(device, fontImageFullPath.c_str());
	if (!result)
	{
		return false;
	}

	return true;
}

void FontClass::Shutdown()
{
	// Release the font texture.
	ReleaseTexture();

	return;
}

bool FontClass::LoadFontData(LPCSTR filename)
{
    std::ifstream fs;
    fs.open(filename);

    std::string tmp;
    int startpos;

    // extract font name
    fs >> tmp >> tmp; // info face="Arial"
    startpos = tmp.find("\"") + 1;
    m_FontData.name = tmp.substr(startpos, tmp.size() - startpos - 1);

    // get font size
    fs >> tmp; // size=73
    startpos = tmp.find("=") + 1;
    m_FontData.size = std::stoi(tmp.substr(startpos, tmp.size() - startpos));

    // bold, italic, charset, unicode, stretchH, smooth, aa, padding, spacing
    fs >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp; // bold=0 italic=0 charset="" unicode=0 stretchH=100 smooth=1 aa=1

    // get padding
    fs >> tmp; // padding=5,5,5,5
    startpos = tmp.find("=") + 1;
    tmp = tmp.substr(startpos, tmp.size() - startpos); // 5,5,5,5

    // get up padding
    startpos = tmp.find(",") + 1;
    m_FontData.toppadding = std::stoi(tmp.substr(0, startpos)) / (float)m_windowInfo->m_screenWidth;

    // get right padding
    tmp = tmp.substr(startpos, tmp.size() - startpos);
    startpos = tmp.find(",") + 1;
    m_FontData.rightpadding = std::stoi(tmp.substr(0, startpos)) / (float)m_windowInfo->m_screenWidth;

    // get down padding
    tmp = tmp.substr(startpos, tmp.size() - startpos);
    startpos = tmp.find(",") + 1;
    m_FontData.bottompadding = std::stoi(tmp.substr(0, startpos)) / (float)m_windowInfo->m_screenWidth;

    // get left padding
    tmp = tmp.substr(startpos, tmp.size() - startpos);
    m_FontData.leftpadding = std::stoi(tmp) / (float)m_windowInfo->m_screenWidth;

    fs >> tmp; // spacing=0,0

    // get lineheight (how much to move down for each line), and normalize (between 0.0 and 1.0 based on size of font)
    fs >> tmp >> tmp; // common lineHeight=95
    startpos = tmp.find("=") + 1;
    m_FontData.lineHeight = (float)std::stoi(tmp.substr(startpos, tmp.size() - startpos)) / (float)m_windowInfo->m_screenHeight;

    // get base height (height of all characters), and normalize (between 0.0 and 1.0 based on size of font)
    fs >> tmp; // base=68
    startpos = tmp.find("=") + 1;
    m_FontData.baseHeight = (float)std::stoi(tmp.substr(startpos, tmp.size() - startpos)) / (float)m_windowInfo->m_screenHeight;

    // get texture width
    fs >> tmp; // scaleW=512
    startpos = tmp.find("=") + 1;
    m_FontData.textureWidth = std::stoi(tmp.substr(startpos, tmp.size() - startpos));

    // get texture height
    fs >> tmp; // scaleH=512
    startpos = tmp.find("=") + 1;
    m_FontData.textureHeight = std::stoi(tmp.substr(startpos, tmp.size() - startpos));

    // get pages, packed, page id
    fs >> tmp >> tmp; // pages=1 packed=0
    fs >> tmp >> tmp; // page id=0

    // get texture filename
    std::string tmp2;
    fs >> tmp2; // file="Arial.png"
    startpos = tmp2.find("\"") + 1;
    m_FontData.fontImage = tmp2.substr(startpos, tmp2.size() - startpos - 1);

    // get number of characters
    fs >> tmp >> tmp; // chars count=97
    startpos = tmp.find("=") + 1;
    m_FontData.numCharacters = std::stoi(tmp.substr(startpos, tmp.size() - startpos));

    // initialize the character list
    m_FontData.CharList = new FontChar[m_FontData.numCharacters];

    for (int c = 0; c < m_FontData.numCharacters; ++c)
    {
        // get unicode id
        fs >> tmp >> tmp; // char id=0
        startpos = tmp.find("=") + 1;
        m_FontData.CharList[c].id = std::stoi(tmp.substr(startpos, tmp.size() - startpos));

        // get x
        fs >> tmp; // x=392
        startpos = tmp.find("=") + 1;
        m_FontData.CharList[c].u = (float)std::stoi(tmp.substr(startpos, tmp.size() - startpos)) / (float)m_FontData.textureWidth;

        // get y
        fs >> tmp; // y=340
        startpos = tmp.find("=") + 1;
        m_FontData.CharList[c].v = (float)std::stoi(tmp.substr(startpos, tmp.size() - startpos)) / (float)m_FontData.textureHeight;

        // get width
        fs >> tmp; // width=47
        startpos = tmp.find("=") + 1;
        tmp = tmp.substr(startpos, tmp.size() - startpos);
        m_FontData.CharList[c].width = (float)std::stoi(tmp) / (float)m_windowInfo->m_screenWidth;
        m_FontData.CharList[c].twidth = (float)std::stoi(tmp) / (float)m_FontData.textureWidth;

        // get height
        fs >> tmp; // height=57
        startpos = tmp.find("=") + 1;
        tmp = tmp.substr(startpos, tmp.size() - startpos);
        m_FontData.CharList[c].height = (float)std::stoi(tmp) / (float)m_windowInfo->m_screenHeight;
        m_FontData.CharList[c].theight = (float)std::stoi(tmp) / (float)m_FontData.textureHeight;

        // get xoffset
        fs >> tmp; // xoffset=-6
        startpos = tmp.find("=") + 1;
        m_FontData.CharList[c].xoffset = (float)std::stoi(tmp.substr(startpos, tmp.size() - startpos)) / (float)m_windowInfo->m_screenWidth;

        // get yoffset
        fs >> tmp; // yoffset=16
        startpos = tmp.find("=") + 1;
        m_FontData.CharList[c].yoffset = (float)std::stoi(tmp.substr(startpos, tmp.size() - startpos)) / (float)m_windowInfo->m_screenHeight;

        // get xadvance
        fs >> tmp; // xadvance=65
        startpos = tmp.find("=") + 1;
        m_FontData.CharList[c].xadvance = (float)std::stoi(tmp.substr(startpos, tmp.size() - startpos)) / (float)m_windowInfo->m_screenWidth;

        // get page
        // get channel
        fs >> tmp >> tmp; // page=0    chnl=0
    }

    // get number of kernings
    fs >> tmp >> tmp; // kernings count=96
    startpos = tmp.find("=") + 1;
    m_FontData.numKernings = std::stoi(tmp.substr(startpos, tmp.size() - startpos));

    // initialize the kernings list
    m_FontData.KerningsList = new FontKerning[m_FontData.numKernings];

    for (int k = 0; k < m_FontData.numKernings; ++k)
    {
        // get first character
        fs >> tmp >> tmp; // kerning first=87
        startpos = tmp.find("=") + 1;
        m_FontData.KerningsList[k].firstid = std::stoi(tmp.substr(startpos, tmp.size() - startpos));

        // get second character
        fs >> tmp; // second=45
        startpos = tmp.find("=") + 1;
        m_FontData.KerningsList[k].secondid = std::stoi(tmp.substr(startpos, tmp.size() - startpos));

        // get amount
        fs >> tmp; // amount=-1
        startpos = tmp.find("=") + 1;
        int t = (float)std::stoi(tmp.substr(startpos, tmp.size() - startpos));
        m_FontData.KerningsList[k].amount = (float)t / (float)m_windowInfo->m_screenWidth;
    }

    return true;
}

bool FontClass::LoadTexture(ID3D11Device* device, LPCSTR filename)
{
	bool result;

	// Create the texture object.
	m_Texture = new TextureClass;
	if (!m_Texture)
	{
		return false;
	}

	// Initialize the texture object.
	result = m_Texture->Initialize(device, filename);
	if (!result)
	{
		return false;
	}

	return true;
}

void FontClass::ReleaseTexture()
{
	// Release the texture object.
	if (m_Texture)
	{
		m_Texture->Shutdown();
		delete m_Texture;
		m_Texture = 0;
	}

	return;
}

ID3D11ShaderResourceView* FontClass::GetTexture()
{
	return m_Texture->GetTexture();
}

void FontClass::BuildVertexArray(void* vertices, char* text, float drawX, float drawY)
{
	VertexType* vertexPtr;
	int numLetters, index, i;

	// Coerce the input vertices into a VertexType structure.
	vertexPtr = (VertexType*)vertices;

	// Get the number of letters in the text.
	numLetters = (int)strlen(text);

	// Initialize the index to the vertex array.
	index = 0;

	D3DXVECTOR2 padding = D3DXVECTOR2(0.5f, 0.0f);
	D3DXVECTOR2 scale = D3DXVECTOR2(1.0f, 1.0f);

    float topLeftScreenX = (drawX * 2.0f) - 1.0f;
    float topLeftScreenY = ((1.0f - drawY) * 2.0f) - 1.0f;

    float x = topLeftScreenX;
    float y = topLeftScreenY;

    //new x and y
    float nx, ny;
    //new width and height
    float nw, nh;

    float horrizontalPadding = (m_FontData.leftpadding + m_FontData.rightpadding) * padding.x;
    float verticalPadding = (m_FontData.toppadding + m_FontData.bottompadding) * padding.y;

	// Draw each letter onto a quad.
	for (i = 0; i < numLetters; ++i)
	{
        char lastChar = -1; // no last character to start with

        char c = text[i];

        FontChar* fc = m_FontData.GetChar(c);

        // character not in font char set
        if (fc == nullptr)
            continue;

        // new line
        if (c == '\n')
        {
            x = topLeftScreenX;
            y -= (m_FontData.lineHeight + verticalPadding) * scale.y;
            continue;
        }

        float kerning = 0.0f;
        if (i > 0)
            kerning = m_FontData.GetKerning(lastChar, c);

        nx = x + ((fc->xoffset + kerning) * scale.x);
        ny = y - (fc->yoffset * scale.y);
        nw = fc->width * scale.x;
        nh = fc->height * scale.y;

        // First triangle in quad.
        vertexPtr[index].position = D3DXVECTOR3(nx, ny, 0.0f);  // Top left.
        vertexPtr[index].texture = D3DXVECTOR2(fc->u, fc->v);
        index++;

        vertexPtr[index].position = D3DXVECTOR3(nx + nw, ny - nh, 0.0f);  // Bottom right.
        vertexPtr[index].texture = D3DXVECTOR2(fc->u + fc->twidth, fc->v + fc->theight);
        index++;

        vertexPtr[index].position = D3DXVECTOR3(nx, ny - nh, 0.0f);  // Bottom left.
        vertexPtr[index].texture = D3DXVECTOR2(fc->u, fc->v + fc->theight);
        index++;

        // Second triangle in quad.
        vertexPtr[index].position = D3DXVECTOR3(nx, ny, 0.0f);  // Top left.
        vertexPtr[index].texture = D3DXVECTOR2(fc->u, fc->v);
        index++;

        vertexPtr[index].position = D3DXVECTOR3(nx + nw, ny, 0.0f);  // Top right.
        vertexPtr[index].texture = D3DXVECTOR2(fc->u + fc->twidth, fc->v);
        index++;

        vertexPtr[index].position = D3DXVECTOR3(nx + nw, ny - nh, 0.0f);  // Bottom right.
        vertexPtr[index].texture = D3DXVECTOR2(fc->u + fc->twidth, fc->v + fc->theight);
        index++;

        // remove horrizontal padding and advance to next char position
        x += (fc->xadvance - horrizontalPadding) * scale.x;

        lastChar = c;
	}
}
