#include "stdafx.h"
#include "Physics/RigidBody.h"
#include "Physics/ICollider.h"


RigidBody::~RigidBody()
{
	Release();
}
void RigidBody::Release()
{
	if (rigidBody) { rigidBody.reset(); }
	if (myMotionState) { myMotionState.reset(); }
	rigidBody = nullptr;
	myMotionState = nullptr;
}
void RigidBody::Create(RigidBodyInfo& rbInfo)
{

	Release();
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(rbInfo.pos.x, rbInfo.pos.y, rbInfo.pos.z));
	transform.setRotation(btQuaternion(rbInfo.rot.x, rbInfo.rot.y, rbInfo.rot.z, rbInfo.rot.w));
	myMotionState = std::make_unique<btDefaultMotionState>();
	myMotionState->setWorldTransform(transform);
	btRigidBody::btRigidBodyConstructionInfo btRbInfo(rbInfo.mass, myMotionState.get(), rbInfo.collider->GetBody(), btVector3(0, 0, 0));
	//çÑëÃÇçÏê¨ÅB
	rigidBody = std::make_unique<btRigidBody>(btRbInfo);

}
