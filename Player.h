#pragma once
#include "Engine/GameObject.h"
#include "Engine/Transform.h"
class FBX;
class BoxCollider;
class Stage;
class HP;

const int PBOX_NUM = 4;

class Player :
    public GameObject
{
	const float JUMP_HEIGHT = 1.0f * 10.0f;//ジャンプの高さ
	const float GRAVITY = 9.0f / 650.0f;    //重力加速度

	BoxCollider* PboxColl_[PBOX_NUM];
	Stage* stage_;
	HP* hp_;

	int hPlayer_;

	Dir pDir_;
	float jumpSpeed_;//ジャンプの高さ
	int Ground_;//地面
	float CameraStopGround_;//これより下にいくとカメラがプレイヤーを追わなくなる
	float DeathGround_;//ここまで落ちたらゲームオーバー
	bool isLeftMove_, isRightMove_, isJump_;//左右移動とジャンプができるかの判定

	void MovePlayer();//プレイヤー移動
public:

	Player(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	void SetGround(const float& ground) { Ground_ = ground; }

	void SetPositionXY(const float& x, const float& y) { transform_.position_ = { x,y,0 }; }//プレイヤーのポジション
	XMFLOAT3 GetPosition() { return transform_.position_; }

	void RotPlayer(const Dir& dir);//プレイヤーの向きを変える
	Dir GetpDir() { return pDir_; }

	void PlayerCollision();//プレイヤーの当たり判定周りの処理関数

	//CameraStopGround_を設定しそれを元にDeathGround_の設定もする
	void SetCameraStopandDeathGround_(const float& Ground) { CameraStopGround_ = Ground; 
	                                                          DeathGround_ = CameraStopGround_ - 20;}
};

