#include "stdafx.h"
#include "BackGround.h"
#include "Bullet.h"
ID3D11ShaderResourceView* normalMapSRV = nullptr; //法線マップ。
ID3D11ShaderResourceView* specMapSRV = nullptr;//スペキュラマップ。

BackGround::BackGround()
{
	static const wchar_t* stageFilePaths[] = {
		L"Assets/modelData/stage_3_1.cmo",
		L"Assets/modelData/stage_3_2.cmo",
		L"Assets/modelData/stage_3_3.cmo",
		L"Assets/modelData/stage_3_4.cmo",
	};
	//法線マップをロード。
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
		g_graphicsEngine->GetD3DDevice(), L"Resource/sprite/Plates_Normal.dds", 0,
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

	//スペキュラマップをロードする。
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

	for (int i = 0; i < eStateParts_Num; i++) {
		//モデルのロード。
		m_model[i].Init(stageFilePaths[i]);
		//シャドウレシーバーのフラグを設定する。
		m_model[i].SetShadowReciever(true);
		//コライダー作成。
		m_physicsStaticObject[i].CreateMeshObject(m_model[i], m_position, m_rotation);
		//ゴースト作成。
		m_GhostObj[i].CreateMesh(m_position, m_rotation, m_model[i]);
		//スキンモデルに法線マップを設定する。
		m_model[i].SetNormalMap(normalMapSRV);
		//スキンモデルにスペキュラマップを設定する。
		m_model[i].SetSpecularMap(specMapSRV);
	}
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
	//弾と当たり判定を取る。
	g_goMgr.QueryGameObject<Bullet>(bullet, [&](Bullet * bul)->bool
		{
			CharacterController& m_chara = *bul->GetCharaCon();
			g_physics.ContactTest(m_chara, [&](const btCollisionObject& contactObject) {
				for (int i = 0; i < eStateParts_Num; i++) {
					if (m_GhostObj[i].IsSelf(contactObject) == true) {
						//弾がステージに当たったら、弾を削除する。
						g_goMgr.DeleteGameObject(bul);
					}
				}
				});
			return true;
		});
	for (auto& model : m_model) {
		model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One());
	}
}

void BackGround::Render()
{
	for (auto& model : m_model) {
		//描画。
		model.Draw(
			enRenderMode_Normal,
			g_camera3D.GetViewMatrix(),
			g_camera3D.GetProjectionMatrix()
		);
	}
}