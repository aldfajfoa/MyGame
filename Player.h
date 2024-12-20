#pragma once
#include "Engine/GameObject.h"
#include "Engine/Transform.h"
class FBX;
class BoxCollider;
class Stage;

class Player :
    public GameObject
{
	enum Dir//プレイヤーの向き
	{
		LEFT,RIGHT
	};
	Dir pDir;

	const float JUMP_HEIGHT = 1.0f * 10.0f;//ジャンプの高さ
	const float GRAVITY = 9.0f / 650.0f;    //重力加速度

	BoxCollider* PboxColl[4];
	Stage* stage;

	int hPlayer_;
	float jumpSpeed_;//ジャンプの高さ
	int Ground_;
	float CameraStopGround_;//これより下にいくとカメラがプレイヤーを追わなくなる
	float DeathGround_;//ここまで落ちたらゲームオーバー
	bool isLeftMove_, isRightMove_, isJump_;//左右移動とジャンプができるかの判定

	void MovePlayer();//プレイヤー移動
public:
	Player(GameObject* parent);
	~Player();

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	void SetGround(float _ground) { Ground_ = _ground; }

	void SetPositionXY(float x, float y) { transform_.position_ = { x,y,0 }; }//プレイヤーのポジション

	void RotPlayer(Dir dir);//プレイヤーの向きを変える
	Dir GetpDir() { return pDir; }

	void ControlCollision();//プレイヤーの当たり判定周りの処理関数

	//CameraStopGround_を設定しそれを元にDeathGround_の設定もする
	void SetCameraStopandDeathGround_(float _Ground) { CameraStopGround_ = _Ground; 
	                                                   DeathGround_ = CameraStopGround_ - 20;}
};

