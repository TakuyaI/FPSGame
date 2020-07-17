#include "stdafx.h"
#include "BackGround.h"
#include "Bullet.h"
ID3D11ShaderResourceView* normalMapSRV = nullptr;
ID3D11ShaderResourceView* specMapSRV = nullptr;
BackGround::BackGround()
{
	m_model.Init(L"Assets/modelData/stage.cmo");
	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One());
	m_model.SetShadowReciever(true);
	m_physicsStaticObject.CreateMeshObject(m_model, m_position, m_rotation);
	m_GhostObj.CreateMesh(m_position, m_rotation, m_model);

	HRESULT nhr1 = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Resource/sprite/Detail_01_Normal.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &normalMapSRV
	);
	HRESULT nhr2 = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Resource/sprite/Detail_03_Normal.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &normalMapSRV
	);
	HRESULT nhr3 = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Resource/sprite/Light_Normal.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &normalMapSRV
	);
	HRESULT nhr4 = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Resource/sprite/Plates_Normal.dds",0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &normalMapSRV
	);
	HRESULT nhr5 = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Resource/sprite/Walls_Normal.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &normalMapSRV
	);
	HRESULT nhr6 = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Resource/sprite/Walls_02_Normal.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &normalMapSRV
	);
	HRESULT nhr7 = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Resource/sprite/Platforms_Normal.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &normalMapSRV
	);
	m_model.SetNormalMap(normalMapSRV);



	HRESULT shr1 = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Resource/sprite/Detail_01_MetallicSmoothness.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &specMapSRV
	);
	HRESULT shr2 = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Resource/sprite/Detail_03_MetallicSmoothness.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &specMapSRV
	);
	HRESULT shr3 = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Resource/sprite/Light_MetallicSmoothness.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &specMapSRV
	);
	HRESULT shr4 = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Resource/sprite/Plates_MetallicSmoothness.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &specMapSRV
	);
	HRESULT shr5 = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Resource/sprite/Platforms_MetallicSmoothness.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &specMapSRV
	);
	HRESULT shr6 = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Resource/sprite/Walls_02_MetallicSmoothness.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &specMapSRV
	);
	HRESULT shr7 = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Resource/sprite/Walls_MetallicSmoothness.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &specMapSRV
	);

	m_model.SetSpecularMap(specMapSRV);
}


BackGround::~BackGround()
{
	
}

bool BackGround::Start()
{
	return true;
}
void BackGround::Update()
{
	g_goMgr.QueryGameObject<Bullet>(bullet, [&](Bullet * bul)->bool
		{
			CharacterController& m_chara = *bul->GetCharaCon();
			g_physics.ContactTest(m_chara, [&](const btCollisionObject& contactObject) {
				if (m_GhostObj.IsSelf(contactObject) == true) {
					g_goMgr.DeleteGameObject(bul);
				}
				});
			return true;
		});
}
void BackGround::SetRegistShadowCaster()
{
//	g_goMgr.GetShadowMap()->RegistShadowCaster(&m_model);
}

void BackGround::Render()
{
	m_model.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}