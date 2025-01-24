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
	//ポインタ
	Player* pplayer_;
	vector<BoxCollider*> StageboxColl_;

	//ハンドル
	vector<int> hBrocks_;//ブロックのハンドルを持つ配列

	//その他の変数
	int width_; //ステージ幅
	int height_;//ステージ高さ
	//vector<vector<int>> Map_;//マップのデータを持つ配列
	vector<vector<BrockData>> Map_;//マップのデータを持つ配列

public:
	Stage(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	int Getwidth() { return width_; }
	int Getheight() { return height_; }
	vector<vector<BrockData>> GetMap() { return Map_; }
	BoxCollider* GetboxColl(int x,int y){return Map_[x][y].boxColl; }
	vector<BoxCollider*> GetStageboxColl(){return StageboxColl_;}
	void SetMap();
};

