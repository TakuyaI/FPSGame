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
	CVector2 & position,
	CVector4 color,
	float scale
)
{
	DirectX::XMFLOAT2 pos = { position.x , position.y };
	DirectX::FXMVECTOR fontColor = { color.x, color.y , color.z ,color.w };
	spriteBatch->Begin();
	spriteFont->DrawString(spriteBatch.get(), text, pos, fontColor, 0.0f, {1.0f, 1.0f}, scale);
	spriteBatch->End();
}
