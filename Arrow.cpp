#include "Arrow.h"
#include "Player.h"
#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/BoxCollider.h"
#include "Timer.h"

Arrow::Arrow(GameObject* parent)
	:GameObject(parent, "Arrow"),isMove_(true),Gravity_(0.006f),dy_(0.04)
{
	hArrow_ = Model::Load("Arrow.fbx");
	assert(hArrow_ >= 0);
}

void Arrow::Initialize()
{
	timer_ = Instantiate<Timer>(this);
	player_ = GetParent()->FindGameObject<Player>();
	stage_ = GetParent()->FindGameObject<Stage>();

	transform_.position_ = player_->GetPosition();
	transform_.scale_ = { 2,2,2 };
	PisRight_ = player_->GetisRight_();

	if (PisRight_)
	{
		transform_.rotate_.y = 90;
		AboxColl_ = new BoxCollider({ 0.3,0,0 }, { 0.2,0.2,0.2 });
		AddCollider(AboxColl_);
	}
	else
	{
		transform_.rotate_.y = -90;
		AboxColl_ = new BoxCollider({ -0.3,0,0 }, { 0.2,0.2,0.2 });
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
		if (PisRight_)
		{
			transform_.position_.x += MOVE_SPEED;
		}
		else
		{
			transform_.position_.x -= MOVE_SPEED;
		}
	}

	ArrowCollision();
}

void Arrow::Draw()
{
	Model::SetTransform(hArrow_, transform_);
	Model::Draw(hArrow_);
}

void Arrow::ArrowCollision()
{
	for (int i = 0; i < stage_->GetStageboxColl().size(); i++)
	{
		if (AboxColl_->IsHit(stage_->GetStageboxColl()[i]))
		{
			isMove_ = false;
			if (timer_->TimeElapsed(1))
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
