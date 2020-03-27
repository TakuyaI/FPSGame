#pragma once
#include "physics\ICollider.h"
class BoxCollider : public ICollider
{
public:
	BoxCollider();
	~BoxCollider();
	/*!
	* @brief	ボックスコライダーを作成。
	*/
	void Create(const CVector3& size);
	btCollisionShape* GetBody() const override
	{
		return shape;
	}
private:
	btBoxShape * shape;
};

