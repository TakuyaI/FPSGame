#pragma once

class FontRender 
{
public:
	FontRender();
	~FontRender();
	/// <summary>
	/// 文字の描画。
	/// </summary>
	/// <param name="text">文字</param>
	/// <param name="position">座標</param>
	/// <param name="color">色</param>
	/// <param name="scale">サイズ</param>
	void Draw(wchar_t const* text, DirectX::XMFLOAT2 const& position, DirectX::FXMVECTOR color, float scale);

	std::unique_ptr<DirectX::SpriteBatch> spriteBatch;
	std::unique_ptr<DirectX::SpriteFont> spriteFont;
};

