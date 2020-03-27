#include "stdafx.h"
#include "PhysicsGhostObject.h"
#include "physics\BoxCollider.h"
#include "physics\MeshCollider.h"
#include "physics\SphereCollider.h"
#include "physics\CapsuleCollider.h"

PhysicsGhostObject::PhysicsGhostObject()
{
}
PhysicsGhostObject::~PhysicsGhostObject()
{
	Release();
}

using namespace std;

void PhysicsGhostObject::Release()
{
	if (m_isRegistPhysicsWorld == true) {
		PhysicsWorld().RemoveCollisionObject(m_ghostObject);
		m_isRegistPhysicsWorld = false;
	}
}
void PhysicsGhostObject::CreateCommon(CVector3 pos, CQuaternion rot/*, std::unique_ptr<ICollider> collider*/)
{
	//m_collider = move(collider);
	m_ghostObject.setCollisionShape(m_collider->GetBody());
	btTransform btTrans;
	btTrans.setOrigin({ pos.x, pos.y, pos.z });
	btTrans.setRotation({ rot.x, rot.y, rot.z, rot.w });
	m_ghostObject.setWorldTransform(btTrans);

	//物理エンジンに登録。
	//g_physics.Init();
	g_physics.AddCollisionObject(m_ghostObject);
	m_isRegistPhysicsWorld = true;
}
void PhysicsGhostObject::CreateBox(CVector3 pos, CQuaternion rot, CVector3 size)
{
	Release();
	auto boxCollider = make_unique<BoxCollider>();
	boxCollider->Create(size);
	m_collider = move(boxCollider);
	CreateCommon(pos, rot/*, move(boxCollider)*/);
}
void PhysicsGhostObject::CreateCapsule(CVector3 pos, CQuaternion rot, float radius, float height)
{
	Release();
	auto capusuleCollider = make_unique<CapsuleCollider>();
	capusuleCollider->Create(radius, height);
	CreateCommon(pos, rot/*, move(capusuleCollider)*/);
}

void PhysicsGhostObject::CreateSphere(CVector3 pos, CQuaternion rot, float radius)
{
	Release();
	auto sphereCollider = make_unique<SphereCollider>();
	sphereCollider->Create(radius);
	CreateCommon(pos, rot/*, move(sphereCollider)*/);
}
/*!
* @brief	メッシュ形状のゴーストオブジェクトを作成。
*@param[in]	pos					座標。
*@param[in]	rot					回転。
*@param[in]	skinModelData		スキンモデルデータ。
*/
void PhysicsGhostObject::CreateMesh(CVector3 pos, CQuaternion rot, const SkinModel& skinModelData)
{
	Release();
	auto meshCollider = make_unique<MeshCollider>();
	meshCollider->CreateFromSkinModel(skinModelData, nullptr);
	CreateCommon(pos, rot/*, move(meshCollider)*/);
}

