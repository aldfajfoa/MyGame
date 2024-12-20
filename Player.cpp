#include "Player.h"
#include "Stage.h"
#include "Arrow.h"
#include "Engine/FBX.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include "Engine/BoxCollider.h"
#include "Engine/SceneManager.h"

Player::Player(GameObject* parent)
	:GameObject(parent,"Player"), hPlayer_(-1), Ground_(0), isLeftMove_(true), isRightMove_(true),isJump_(true),pDir(RIGHT)
{
	jumpSpeed_ = 0.0f;
}

Player::~Player()
{
}

void Player::Initialize()
{
	hPlayer_ = Model::Load("Player.fbx");
	assert(hPlayer_ >= 0);
	transform_.rotate_.y = 90;

	//上下左右の当たり判定
	PboxColl[0] = new BoxCollider({ -0.3, 0.1,0 }, { 0.3,1.0,0.1 });//左
	PboxColl[1] = new BoxCollider({  0.5, 0.1,0 }, { 0.3,1.0,0.1 });//右
	PboxColl[2] = new BoxCollider({  0.1, 0.7,0 }, { 0.5,0.3,0.1 });//上
	PboxColl[3] = new BoxCollider({  0.1,-20, 0 }, { 0.5, 40,0.1 });//下
	for (int i = 0; i < 4; i++)
	{
		AddCollider(PboxColl[i]);
	}

	stage = GetParent()->FindGameObject<Stage>();
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
		XMFLOAT3 t = { transform_.position_.x,transform_.position_.y,transform_.position_.z };
		XMFLOAT3 p = { transform_.position_.x,transform_.position_.y,-10 + transform_.position_.z };
		Camera::SetTarget(t);
		Camera::SetPosition(p);
	}
	else if (transform_.position_.y < DeathGround_)//ゲームオーバー
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_OVER);
	}

	ControlCollision();

	if (Input::IsKeyDown(DIK_J))//矢を撃つ
	{
		Instantiate<Arrow>(this);
	}
}

void Player::Draw()
{
	Model::SetTransform(hPlayer_, transform_);
	Model::Draw(hPlayer_);
}

void Player::Release()
{
}

void Player::RotPlayer(Dir dir)
{
	if (dir == LEFT)
	{
		if (transform_.rotate_.y != -90)
		{
			transform_.rotate_.y -= 30;
		}
	}

	if (dir == RIGHT)
	{
		if (transform_.rotate_.y != 90)
		{
			transform_.rotate_.y += 30;
		}
	}
}

void Player::ControlCollision()
{
	//左当たり判定
	for (int i = 0; i < stage->GetStageboxColl().size(); i++)
	{
		if (PboxColl[0]->IsHit(stage->GetStageboxColl()[i])) {
			isLeftMove_ = false;
			break;
		}
		else
		{
			isLeftMove_ = true;
		}
	}

	//右当たり判定
	for (int i = 0; i < stage->GetStageboxColl().size(); i++)
	{
		if (PboxColl[1]->IsHit(stage->GetStageboxColl()[i])) {
			isRightMove_ = false;
			break;
		}
		else
		{
			isRightMove_ = true;
		}
	}

	//上当たり判定
	for (int i = 0; i < stage->GetStageboxColl().size(); i++)
	{
		if (isJump_) {
			if (PboxColl[2]->IsHit(stage->GetStageboxColl()[i])) {
				jumpSpeed_ = 0;
				isJump_ = false;
				break;
			}
		}
	}

	//下当たり判定
	for (int i = 0; i < stage->GetStageboxColl().size(); i++)
	{
		if (PboxColl[3]->IsHit(stage->GetStageboxColl()[i])) {
			Ground_ = stage->GetStageboxColl()[i]->Getcenter().y+0.5;
			break;
		}
		else
		{
			Ground_ = -999;
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
	if (Input::IsKey(DIK_LEFT))
	{
		pDir = LEFT;
	}

	if (isRightMove_)
	{
		if (Input::IsKey(DIK_RIGHT))//右へ進む
		{
			transform_.position_.x += 0.05;
		}
	}
	if (Input::IsKey(DIK_RIGHT))//右へ進む
	{
		pDir = RIGHT;
	}

	if (isJump_)
	{
		if (Input::IsKey(DIK_SPACE))//ジャンプ
		{
			jumpSpeed_ = -sqrtf(GRAVITY * JUMP_HEIGHT);
		}
	}


	jumpSpeed_ += GRAVITY;//速度+=加速度
	transform_.position_.y -= jumpSpeed_;//座標+=速度

	RotPlayer(pDir);
}

