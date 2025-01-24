#include "Player.h"
#include "Stage.h"
#include "Arrow.h"
#include "PlayScene.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include "Engine/BoxCollider.h"
#include "Engine/SceneManager.h"
#include "Engine/Debug.h"

Player::Player(GameObject* parent)
	:GameObject(parent,"Player"), hPlayer_(-1), Ground_(0),isLeftMove_(true), isRightMove_(true),isJump_(true), isRight_(true)
{
	jumpSpeed_ = 0.0f;
}

void Player::Initialize()
{
	hPlayer_ = Model::Load("Player.fbx");
	assert(hPlayer_ >= 0);
	transform_.rotate_.y = 90;

	//上下左右の当たり判定(ブロックやギミックとの判定用)
	PboxColl_[0] = new BoxCollider({ -0.3, 0.1, 0 }, { 0.3,   1, 0.1 });//左
	PboxColl_[1] = new BoxCollider({  0.5, 0.1, 0 }, { 0.3,   1, 0.1 });//右
	PboxColl_[2] = new BoxCollider({  0.1, 0.7, 0 }, { 0.5, 0.3, 0.1 });//上
	PboxColl_[3] = new BoxCollider({  0.1,-0.5, 0 }, { 0.5,   1, 0.1 });//下
	//中心(敵やゴールとの判定用)
	PboxColl_[4] = new BoxCollider({  0,   0.1, 0 }, { 0.7, 1.2, 0.1 });
	for (int i = 0; i < PBOX_NUM; i++)
	{
		AddCollider(PboxColl_[i]);
	}

	stage_ = GetParent()->FindGameObject<Stage>();
}

void Player::Update()
{
	MovePlayer();

	if (transform_.position_.y < Ground_) {
		transform_.position_.y = Ground_;
		jumpSpeed_ = 0.0f;
		isJump_ = true;
	}
	
	if (transform_.position_.y > CameraStopGround_)//ここでカメラが止まる
	{
		XMFLOAT3 t = { transform_.position_.x,transform_.position_.y+1,transform_.position_.z };
		XMFLOAT3 p = { transform_.position_.x,transform_.position_.y+1,-10 + transform_.position_.z };
		Camera::SetTarget(t);
		Camera::SetPosition(p);
	}
	else if (transform_.position_.y < DeathGround_)//ゲームオーバー
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_OVER);
	}

	if (Input::IsKeyDown(DIK_F))//矢を撃つ
	{
		Instantiate<Arrow>(FindObject("PlayScene"));
	}

	isLeftMove_ = true;
	isRightMove_ = true;
	Ground_ = -999;
}

void Player::Draw()
{
	Model::SetTransform(hPlayer_, transform_);
	Model::Draw(hPlayer_);
}

void Player::Release()
{
}

void Player::RotPlayer(const bool& isRight)
{
	if (isRight_ == false)
	{
		if (transform_.rotate_.y != -90)
		{
			transform_.rotate_.y -= 30;
		}
	}

	if (isRight_)
	{
		if (transform_.rotate_.y != 90)
		{
			transform_.rotate_.y += 30;
		}
	}
}

void Player::OnCollision(GameObject* pTarget)
{
	//左
	for (int y = 0; y < stage_->Getheight(); y++)
	{
		for (int x = 0; x < stage_->Getwidth(); x++)
		{
			if (stage_->GetboxColl(y, x) != nullptr)//ブロックが999(空白)じゃなかったら当たり判定
			{
				if (PboxColl_[LEFT]->IsHit(stage_->GetMap()[y][x].boxColl)) {
					isLeftMove_ = false;//当たったら左に進めなくする
					break;
				}
			}
		}
	}

	//右
	for (int y = 0; y < stage_->Getheight(); y++)
	{
		for (int x = 0; x < stage_->Getwidth(); x++)
		{
			if (stage_->GetboxColl(y, x) != nullptr)//ブロックが999(空白)じゃなかったら当たり判定
			{
				if (PboxColl_[RIGHT]->IsHit(stage_->GetMap()[y][x].boxColl)) {
					isRightMove_ = false;//当たったら右に進めなくする
					break;
				}
			}
		}
	}

	//上当たり判定
	for (int y = 0; y < stage_->Getheight(); y++)
	{
		for (int x = 0; x < stage_->Getwidth(); x++)
		{
			if (stage_->GetboxColl(y, x) != nullptr)//ブロックが999(空白)じゃなかったら当たり判定
			{
				if (isJump_) {
					if (PboxColl_[TOP]->IsHit(stage_->GetMap()[y][x].boxColl)) {
						jumpSpeed_ = 0;
						isJump_ = false;
						break;
					}
				}
			}
		}
	}

	//下当たり判定
	for (int y = 0; y < stage_->Getheight(); y++)
	{
		for (int x = 0; x < stage_->Getwidth(); x++)
		{
			if (stage_->GetboxColl(y, x) != nullptr)//ブロックが999(空白)じゃなかったら当たり判定
			{
				if (PboxColl_[UNDER]->IsHit(stage_->GetMap()[y][x].boxColl)) {
					Ground_ = stage_->GetboxColl(y, x)->Getcenter().y + 0.5;
					break;
				}
			}
		}
	}
}

void Player::MovePlayer()
{
	if (isLeftMove_)
	{
		if (Input::IsKey(DIK_LEFT))//左へ進む
		{
			transform_.position_.x -= 0.05;
		}
	}
	if (Input::IsKey(DIK_LEFT))//左向きにする
	{
		isRight_ = false;
	}

	if (isRightMove_)
	{
		if (Input::IsKey(DIK_RIGHT))//右へ進む
		{
			transform_.position_.x += 0.05;
		}
	}
	if (Input::IsKey(DIK_RIGHT))//右向きにする
	{
		isRight_ = true;
	}

	if (isJump_)
	{
		if (Input::IsKey(DIK_SPACE))//ジャンプ
		{
			jumpSpeed_ = -sqrtf(GRAVITY * JUMP_HEIGHT);
		}
	}


	jumpSpeed_ += GRAVITY;
	transform_.position_.y -= jumpSpeed_;

	RotPlayer(isRight_);
}

