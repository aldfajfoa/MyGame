#include "Beast.h"
#include "Stage.h"
#include "Arrow.h"
#include "Player.h"
#include "HP.h"
#include "Engine/Model.h"
#include "Engine/BoxCollider.h"
#include "Engine/SphereCollider.h"

#include "Engine/Input.h"//デバッグ用

Beast::Beast(GameObject* parent)
	:GameObject(parent, "Beast"), hBeast_(-1), Ground_(0), isLeftMove_(true), isRightMove_(true), isJump_(true), isRight_(false),isChase_(false)
{
	hBeast_ = Model::Load("Beast.fbx");
	assert(hBeast_ >= 0);
	transform_.rotate_.y = -90;
	BeastHp_ = BEAST_HP;
}

void Beast::Initialize()
{
	//上下左右の当たり判定(ブロックやギミックとの判定用)
	BboxColl_[0] = new BoxCollider({ -0.5, 0.08, 0 }, { 0.3, 0.8, 0.1 });//左
	BboxColl_[1] = new BoxCollider({  0.5, 0.08, 0 }, { 0.3, 0.8, 0.1 });//右
	BboxColl_[2] = new BoxCollider({    0,  0.5, 0 }, {   1, 0.3, 0.1 });//上
	BboxColl_[3] = new BoxCollider({  0.1, -0.5, 0 }, {   1,   1, 0.1 });//下
	BboxColl_[4] = new BoxCollider({    0,    0, 0 }, { 1.2, 0.9, 0.1 });//中心

	for (int i = 0; i < BBOX_NUM; i++)
	{
		AddCollider(BboxColl_[i]);
	}

	DetectCircle_ = new SphereCollider({ 0,0,0 }, 5);
	AddCollider(DetectCircle_);

	stage_ = (Stage*)GetParent();
	arrow_ = nullptr;
	player_ = ((Player*)GetParent()->GetParent()->FindGameObject<Player>());
	hp_ = nullptr;
}

void Beast::Update()
{
	if (arrow_ == nullptr)
	{
		arrow_ = ((Arrow*)GetParent()->GetParent()->FindGameObject<Arrow>());
	}

	if (hp_ == nullptr)
	{
		hp_ = ((HP*)GetParent()->GetParent()->FindGameObject<HP>());
	}

	if (BeastHp_ == 0)
	{
		KillMe();
	}

	MoveBeast();

	if (transform_.position_.y < Ground_) {
		transform_.position_.y = Ground_;
		jumpSpeed_ = 0.0f;
		isJump_ = true;
	}

	isLeftMove_ = true;
	isRightMove_ = true;
	isChase_ = false;
	Ground_ = -999;
}

void Beast::Draw()
{
	Model::SetTransform(hBeast_, transform_);
	Model::Draw(hBeast_);
}

void Beast::Release()
{
}

void Beast::RotBeast(const bool& isRight)
{
	if (isRight_ == false)
	{
		if (transform_.rotate_.y != -90)
		{
			transform_.rotate_.y -= 30;
		}
	}
	else
	{
		if (transform_.rotate_.y != 90)
		{
			transform_.rotate_.y += 30;
		}
	}
}

void Beast::OnCollision(GameObject* pTarget)
{
	for (int y = 0; y < stage_->Getheight(); y++)
	{
		for (int x = 0; x < stage_->Getwidth(); x++)
		{
			if (stage_->GetboxColl(y, x) != nullptr)//ブロックの当たり判定がnullptr(空白)じゃなかったら当たり判定
			{
				if (BboxColl_[LEFT]->IsHit(stage_->GetboxColl(y, x))) {
					isLeftMove_ = false;//当たったら左に進めなくする
					jumpSpeed_ = -sqrtf(GRAVITY * JUMP_HEIGHT);//ジャンプさせる
				}

				if (BboxColl_[RIGHT]->IsHit(stage_->GetboxColl(y, x))) {
					isRightMove_ = false;//当たったら右に進めなくする
					jumpSpeed_ = -sqrtf(GRAVITY * JUMP_HEIGHT);//ジャンプさせる
				}

				if (isJump_) {
					if (BboxColl_[TOP]->IsHit(stage_->GetboxColl(y, x))) {
						jumpSpeed_ = 0;
						isJump_ = false;
					}
				}

				if (BboxColl_[UNDER]->IsHit(stage_->GetboxColl(y, x))) {
					Ground_ = stage_->GetboxColl(y, x)->Getcenter().y + 0.5;//地面に乗せる
				}
			}
		}
	}

	for (int a = 0; a < player_->GetARROW_NUM(); a++)
	{
		if (BboxColl_[CENTER]->IsHit(player_->Getarrows(a)->GetAboxColl())) {
			player_->Getarrows(a)->ResetArrow();
			BeastHp_--;
		}
	}

	if(DetectCircle_->IsHitBoxVsCircle(player_->GetCenterBoxColl(),DetectCircle_))
	{ 
		isChase_ = true;
	}

	if (BboxColl_[CENTER]->IsHit(player_->GetCenterBoxColl())) {
		hp_->DecreaseHP(40);
	}
}

void Beast::MoveBeast()
{
	if (isChase_)
	{
 		XMFLOAT3 pPos = player_->GetPosition();
		if (transform_.position_.x >= pPos.x)
		{
			isRight_ = false;
		}
		else if (transform_.position_.x <= pPos.x)
		{
			isRight_ = true;
		}
		else
		{
			//isLeftMove_ = false;
			//isRightMove_ = true;
		}
	}
	
	if (isChase_)
	{
		if (isLeftMove_ && isRight_ == false)//左へ進む
		{
			transform_.position_.x -= 0.02;
		}
		if (isRightMove_ && isRight_)//右へ進む
		{
			transform_.position_.x += 0.02;
		}
	}

	jumpSpeed_ += GRAVITY;
	transform_.position_.y -= jumpSpeed_;

	RotBeast(isRight_);
	///////////////////////////////////////
	/*if (Input::IsKey(DIK_A))//左向きにする
	{
		isRight_ = false;
		if (isLeftMove_)//左へ進む
		{
			transform_.position_.x -= 0.05;
		}
	}

	if (Input::IsKey(DIK_D))//右向きにする
	{
		isRight_ = true;
		if (isRightMove_)//右へ進む
		{
			transform_.position_.x += 0.05;
		}
	}

	if (isJump_)
	{
		if (Input::IsKey(DIK_W))//ジャンプ
		{
			jumpSpeed_ = -sqrtf(GRAVITY * JUMP_HEIGHT);
		}
	}

	jumpSpeed_ += GRAVITY;
	transform_.position_.y -= jumpSpeed_;

	RotBeast(isRight_);*/
}