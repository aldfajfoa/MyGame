#pragma once
#include "Engine/GameObject.h"
#include <vector>
using std::vector;
class FBX;
class Player;
class BoxCollider;


class Stage :
    public GameObject
{
	Player* pplayer;
	BoxCollider* StageboxColl;

	int hModel_;
	int width; //ステージ幅
	int height;//ステージ高さ
	vector<vector<int>> Map;//マップのデータを持つ配列

	bool IsWallBlock(int x, int y);//ブロックの判定

public:
	Stage(GameObject* parent);
	~Stage();
	void SetMap();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	//四方向のブロック当たり判定
	int CollisionRight(int x, int y);
	int CollisionLeft(int x, int y);
	int CollisionDown(int x, int y);
	int CollisionUp(int x, int y);
};

