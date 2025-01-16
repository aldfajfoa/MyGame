#pragma once
#include "Engine/GameObject.h"
class Player;
class BoxCollider;
class Stage;

class Arrow :
	public GameObject
{
	const float MOVE_SPEED = 0.4;

	Player* player_;
	Stage* stage_;
	BoxCollider* AboxColl_;

	int hArrow_;

	Dir aDir_;//プレイヤーの左右の向きを持つ変数
	bool isMove_;
	float dy_;
	float Gravity_;

	bool KillTimer(const float& time);//当たってから消えるまでの時間
	void ArrowCollision();
public:
	Arrow(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

