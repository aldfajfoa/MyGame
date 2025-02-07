#include "Vine.h"
#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/BoxCollider.h"

Vine::Vine(GameObject* parent)
	:GameObject(parent, "Vine"),hVine_(-1), hSpinyVine_(-1), hLeafVine_(-1),isMove_(true)
{
	Vines_ = 1;
	addVinesLine_ = 0;
}

void Vine::Initialize()
{
	hVine_ = Model::Load("Vine.fbx");
	assert(hVine_ >= 0);

	vTipColl_ = new BoxCollider({ 0, 0.4, 0 }, { 0.3, 0.2, 0.1 });
	AddCollider(vTipColl_);

	stage_ = (Stage*)GetParent();
}

void Vine::Update()
{
	if (isMove_)
	{
		transform_.position_.y+= 0.05;
		MoveNum_ += 0.05;
	}

	if (MoveNum_ >= addVinesLine_)
	{
		Vines_++;
		addVinesLine_++;
	}

	isMove_ = true;
}

void Vine::Draw()
{
	for (int i = 0; i < Vines_; i++)
	{
		Transform tmp = transform_;
		tmp.position_.y -= i;
		Model::SetTransform(hVine_, tmp);
		Model::Draw(hVine_);
	}
}

void Vine::Release()
{
}

void Vine::OnCollision(GameObject* pTarget)
{
	for (int y = 0; y < stage_->Getheight(); y++)
	{
		for (int x = 0; x < stage_->Getwidth(); x++)
		{
			if (stage_->GetboxColl(y, x) != nullptr)//ブロックの当たり判定がnullptr(空白)じゃなかったら当たり判定
			{
				if (vTipColl_->IsHit(stage_->GetboxColl(y, x))) {
 					isMove_ = false;//当たったら左に進めなくする
				}
			}
		}
	}
}
