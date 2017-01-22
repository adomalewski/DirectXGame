#pragma once

#include "pch.h"

struct TextureInfo {
	TextureInfo()
	{
		scale = 1.0;
	}

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;
	DirectX::SimpleMath::Vector2 screenPos;
	DirectX::SimpleMath::Vector2 origin;
	CD3D11_TEXTURE2D_DESC catDesc;
	LPCWSTR file;
	float scale;
};

enum WindowRegion { TopLeft, TopRight, BottomLeft, BottomRight, Center, CenterTop, CenterBottom, CenterLeft, CenterRight };