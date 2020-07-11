#pragma once

class FontRender 
{
public:
	FontRender();
	~FontRender();
	/// <summary>
	/// �����̕`��B
	/// </summary>
	/// <param name="text">����</param>
	/// <param name="position">���W</param>
	/// <param name="color">�F</param>
	/// <param name="scale">�T�C�Y</param>
	void Draw(wchar_t const* text, DirectX::XMFLOAT2 const& position, DirectX::FXMVECTOR color, float scale);

	std::unique_ptr<DirectX::SpriteBatch> spriteBatch;
	std::unique_ptr<DirectX::SpriteFont> spriteFont;
};

