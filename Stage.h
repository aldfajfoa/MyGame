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
	vector<BoxCollider*> StageboxColl;

	int hModel_;
	int width; //ステージ幅
	int height;//ステージ高さ
	vector<vector<int>> Map;//マップのデータを持つ配列

public:
	Stage(GameObject* parent);
	~Stage();
	vector<BoxCollider*> GetStageboxColl(){return StageboxColl;}
	void SetMap();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

