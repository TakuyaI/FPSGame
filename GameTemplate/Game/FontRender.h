#pragma once

class FontRender 
{
public:
	FontRender();
	~FontRender();

	void Draw(wchar_t const* text, DirectX::XMFLOAT2 const& position, DirectX::FXMVECTOR color);

	std::unique_ptr<DirectX::SpriteBatch> spriteBatch;
	std::unique_ptr<DirectX::SpriteFont> spriteFont;
};

