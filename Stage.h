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
	Player* pplayer_;
	vector<BoxCollider*> StageboxColl_;

	vector<int> hBrocks_;//ブロックのハンドルを持つ配列

	int width_; //ステージ幅
	int height_;//ステージ高さ
	vector<vector<int>> Map_;//マップのデータを持つ配列

public:
	Stage(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	vector<BoxCollider*> GetStageboxColl(){return StageboxColl_;}
	void SetMap();
};

