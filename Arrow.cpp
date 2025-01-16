#include "Arrow.h"
#include "Player.h"
#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/BoxCollider.h"

Arrow::Arrow(GameObject* parent)
	:GameObject(parent, "Arrow"),isMove_(true),Gravity_(0.006f),dy_(0.04)
{
	hArrow_ = Model::Load("Arrow.fbx");
	assert(hArrow_ >= 0);
}

void Arrow::Initialize()
{
	player_ = GetParent()->FindGameObject<Player>();
	stage_ = GetParent()->FindGameObject<Stage>();

	transform_.position_ = player_->GetPosition();
	transform_.scale_ = { 2,2,2 };
	aDir_ = player_->GetpDir();

	if (aDir_ == LEFT)
	{
		transform_.rotate_.y = -90;
		AboxColl_ = new BoxCollider({ -0.3,0,0 }, { 0.2,0.2,0.2 });
		AddCollider(AboxColl_);
	}
	else
	{
		transform_.rotate_.y = 90;
		AboxColl_ = new BoxCollider({ 0.3,0,0 }, { 0.2,0.2,0.2 });
		AddCollider(AboxColl_);
	}
}

void Arrow::Update()
{
	if (isMove_) {

		//重力で少しずつ角度と高度が落ちる
		transform_.position_.y += dy_;
		transform_.rotate_.x += -dy_*20;
		dy_ -= Gravity_;

		//プレイヤーの向きで進む方向を変える
		if (aDir_ == LEFT)
		{
			transform_.position_.x -= MOVE_SPEED;
		}
		else
		{
			transform_.position_.x += MOVE_SPEED;
		}
	}

	ArrowCollision();
}

void Arrow::Draw()
{
	Model::SetTransform(hArrow_, transform_);
	Model::Draw(hArrow_);
}

bool Arrow::KillTimer(const float &time)
{
	static float timer = time;
	timer -= 1.0f / 60.0f;
	if (timer <= 0)
	{
		timer = time;
		return true;
	}
	else
	{
		return false;
	}
}

void Arrow::ArrowCollision()
{
	for (int i = 0; i < stage_->GetStageboxColl().size(); i++)
	{
		if (AboxColl_->IsHit(stage_->GetStageboxColl()[i]))
		{
			isMove_ = false;
			if (KillTimer(1))
			{
				KillMe();
			}
			break;
		}
		else
		{
			isMove_ = true;
		}
	}
}


void Arrow::Release()
{
}
