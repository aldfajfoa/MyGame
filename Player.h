#pragma once
#include "Engine/GameObject.h"
#include "Engine/Transform.h"
class FBX;
class BoxCollider;

class Player :
    public GameObject
{
	const float JUMP_HEIGHT = 1.0f * 3.0f;//ジャンプの高さ
	const float GRAVITY = 8.0f / 650.0f;    //重力加速度

	BoxCollider* PboxColl[4];

	int hModel_;
	void MovePlayer();//プレイヤー移動
	float jumpSpeed_;
	int Ground_;
	bool isMove_;//移動できるか
	bool isLeftMove_, isRightMove_, isJump_;//左右移動とジャンプができるかの判定
public:
	Player(GameObject* parent);
	~Player();

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	void SetGround(float _ground) { Ground_ = _ground; }

	//プレイヤーのポジション
	void SetPositionXY(float x, float y) { transform_.position_ = { x,y,0 }; }

	//プレイヤーの当たり判定周りの処理関数
	void ControlCollision();

	//何かに当たった
	//引数：pTarget 当たった相手
	void OnCollision(GameObject* pTarget) override;
};

