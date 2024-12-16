#include "Player.h"
#include "Stage.h"
#include "Engine/FBX.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include "Engine/BoxCollider.h"

Player::Player(GameObject* parent)
	:GameObject(parent,"Player"),hModel_(-1), Ground_(0),isMove_(true), isLeftMove_(true), isRightMove_(true)
{
	jumpSpeed_ = 0.0f;
}

Player::~Player()
{
}

void Player::Initialize()
{
	hModel_ = Model::Load("Player.fbx");
	assert(hModel_ >= 0);
	transform_.rotate_.y = 90;

	//上下左右の当たり判定
	PboxColl[0] = new BoxCollider({ -0.3,0.1,0 }, { 0.3,1.0,0.1 });//左
	PboxColl[1] = new BoxCollider({ 0.5,0.1,0 }, { 0.3,1.0,0.1 });//右
	//PboxColl[0] = new BoxCollider({ 0,0.2,0 }, { 0.8,1.1,0.5 });//上
	//PboxColl[0] = new BoxCollider({ 0,0.2,0 }, { 0.8,1.1,0.5 });//下

	//for (int i = 0; i < 4; i++)
	//{
		AddCollider(PboxColl[0]);
		AddCollider(PboxColl[1]);
	//}
	stage = GetParent()->FindGameObject<Stage>();
}

void Player::Update()
{
	MovePlayer();

	if (transform_.position_.y < Ground_) {
		transform_.position_.y = Ground_;
		jumpSpeed_ = 0.0f;
	}

	XMFLOAT3 t = { transform_.position_.x,transform_.position_.y,transform_.position_.z };
	XMFLOAT3 p = { transform_.position_.x,transform_.position_.y,-10 + transform_.position_.z };
	
	Camera::SetTarget(t);
	Camera::SetPosition(p);

	ControlCollision();
}

void Player::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Player::Release()
{
}

void Player::ControlCollision()
{
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

	if (isRightMove_)
	{
		if (Input::IsKey(DIK_RIGHT))//右へ進む
		{
			transform_.position_.x += 0.05;
		}
	}

	if (Input::IsKey(DIK_SPACE))//ジャンプ
	{
		jumpSpeed_ = -sqrtf(GRAVITY * JUMP_HEIGHT);
	}

	jumpSpeed_ += GRAVITY;//速度+=加速度
	transform_.position_.y -= jumpSpeed_;//座標+=速度
}

