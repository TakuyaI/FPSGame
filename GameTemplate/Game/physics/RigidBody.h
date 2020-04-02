#pragma once



class ICollider;

//���̏��B
struct RigidBodyInfo {

	CVector3 pos = CVector3::Zero();			//���W�B
	CQuaternion rot = CQuaternion::Identity();	//��]�B
	ICollider* collider = nullptr;				//�R���C�_�[�B
	float mass = 0.0f;							//���ʁB

};
//���̃N���X�B
class RigidBody
{
	std::unique_ptr<btRigidBody>			rigidBody = nullptr;		//���́B
	std::unique_ptr<btDefaultMotionState>	myMotionState = nullptr;	//���[�V�����X�e�[�g�B
public:

	~RigidBody();
	void Release();
	void Create(RigidBodyInfo& rbInfo);
	btRigidBody* GetBody()
	{
		return rigidBody.get();
	}
};

