#include "Stage.h"
#include "Player.h"
#include "Gool.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/CsvReader.h"
#include "Engine/BoxCollider.h"
#include <string>
using std::string;

Stage::Stage(GameObject* parent)
	:GameObject(parent, "Stage")
{
}

void Stage::SetMap()
{
	if (Map_.empty()) 
	{
		Map_.clear();
	}
	CsvReader csv;//データを読むクラスのインスタンスを作成
	bool ret = csv.Load("Stage.csv");
	assert(ret);
	width_ = csv.GetWidth(0);//横幅を取得
	height_ = csv.GetHeight();

	Map_.resize(height_, vector<int>(width_));//サイズを変更

	int wholeheight = height_;//全体の縦幅
	height_ = (wholeheight - 1) / 2;//マップの縦幅取得

	int scount = 0;
	for (int h = 0; h < height_; h++)
	{
		for (int w = 0; w < width_; w++)
		{
			Map_[h][w] = csv.GetInt(w, h);
			switch (Map_[h][w])
			{
			case 100:
			case 101:
			{
				StageboxColl_.push_back(new BoxCollider({ (float)w,(float)-h,0 }, { 1.0,1.0,1.0 }));
				AddCollider(StageboxColl_[scount]);
				scount++;
			}
			break;
			}
		}
	}

	scount = 0;

	for (int h = 0; h < height_; h++)
	{
		for (int w = 0; w < width_; w++)
		{
			switch (csv.GetInt(w, h + height_ + 1))
			{
			case 0://プレイヤー
			{
				pplayer_ = GetParent()->FindGameObject<Player>();
				pplayer_->SetPositionXY(w, -h);
				pplayer_->SetGround(-h);
				break;
			}
			case 20://ゴール
			{
				Gool* g = Instantiate<Gool>(this);
				g->SetPositionXY(w, -h);
			}
			break;
			}
		}
	}

	pplayer_->SetCameraStopandDeathGround_(-height_);
}

void Stage::Initialize()
{
	hBrocks_.push_back(Model::Load("Box.fbx"));
	hBrocks_.push_back(Model::Load("Box2.fbx"));

	for (int i = 0; i < hBrocks_.size(); i++)
	{
		assert(hBrocks_[i] >= 0);
	}
}

void Stage::Update()
{
}

void Stage::Draw()
{
	Transform t;
	
	for (float y = 0; y < height_; y++)
	{
		for (float x = 0; x < width_; x++)
		{
			switch (Map_[y][x])
			{
			case 100:
			{
				t.position_ = { x,-y,0 };
				Model::SetTransform(hBrocks_[Map_[y][x]-100], t);
				Model::Draw(hBrocks_[Map_[y][x] - 100]);
				break;
			}
			case 101:
			{
				t.position_ = { x,-y,0 };
				Model::SetTransform(hBrocks_[Map_[y][x] - 100], t);
				Model::Draw(hBrocks_[Map_[y][x] - 100]);
				break;
			}
			default:
				break;
			}
		}
	}
}

void Stage::Release()
{
}
