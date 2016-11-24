#pragma once

#include "pch.h"

struct FontInfo {
	std::unique_ptr<DirectX::SpriteFont> font;
	LPCWSTR file;
};

struct TextInfo {
	LPCWSTR text;
	DirectX::SimpleMath::Vector2 screenPos;
	DirectX::SimpleMath::Vector2 origin;
	Vector2 strMeasure;
};