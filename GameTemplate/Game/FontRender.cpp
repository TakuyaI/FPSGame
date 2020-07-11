#include "stdafx.h"
#include "FontRender.h"


FontRender::FontRender()
{
	spriteBatch = std::make_unique<DirectX::SpriteBatch>(g_graphicsEngine->GetD3DDeviceContext());
	spriteFont = std::make_unique<DirectX::SpriteFont>(g_graphicsEngine->GetD3DDevice(), L"Assets/font/myfile.spritefont");
}


FontRender::~FontRender()
{
}

void FontRender::Draw(
	wchar_t const* text,
	DirectX::XMFLOAT2 const& position,
	DirectX::FXMVECTOR color,
	float scale
)
{
	spriteBatch->Begin();
	spriteFont->DrawString(spriteBatch.get(), text, position, color, 0.0f, {1.0f, 1.0f}, scale);
	spriteBatch->End();
}
