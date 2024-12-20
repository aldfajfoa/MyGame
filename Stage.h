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

	int width; //ステージ幅
	int height;//ステージ高さ
	vector<int> hBrocks_;//ブロックのデータを持つ配列
	vector<vector<int>> Map;//マップのデータを持つ配列

public:
	Stage(GameObject* parent);
	~Stage();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	vector<BoxCollider*> GetStageboxColl(){return StageboxColl;}
	//int GetModelHandle() { return (hModel_); }
	void SetMap();
};

