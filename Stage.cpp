#include "Stage.h"
#include "Player.h"
#include "Engine/FBX.h"
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

Stage::~Stage()
{
}

void Stage::SetMap()
{
	if (Map.empty()) 
	{
		Map.clear();
	}
	CsvReader csv;//データを読むクラスのインスタンスを作成
	bool ret = csv.Load("Stage.csv");
	assert(ret);
	width = csv.GetWidth(0);//横幅を取得
	height = csv.GetHeight();

	Map.resize(height, vector<int>(width));//サイズを変更

	int wholeheight = height;//全体の縦幅
	height = (wholeheight - 1) / 2;//マップの縦幅取得

	int scount = 0;
	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			Map[h][w] = csv.GetInt(w, h);
			switch (Map[h][w])
			{
			case 100:
			case 101:
			{
				StageboxColl.push_back(new BoxCollider({ (float)w,(float)-h,0 }, { 1.0,1.0,1.0 }));
				AddCollider(StageboxColl[scount]);
				scount++;
			}
			break;
			}
		}
	}

	scount = 0;

	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			switch (csv.GetInt(w, h + height + 1))
			{
			case 0://プレイヤー
			{
				pplayer = GetParent()->FindGameObject<Player>();
				pplayer->SetPositionXY(w, -h);
				pplayer->SetGround(-h);
			}
			break;
			}
		}
	}

	pplayer->SetCameraStopandDeathGround_(-height);
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
	
	for (float y = 0; y < height; y++)
	{
		for (float x = 0; x < width; x++)
		{
			switch (Map[y][x])
			{
			case 100:
			{
				t.position_ = { x,-y,0 };
				Model::SetTransform(hBrocks_[Map[y][x]-100], t);
				Model::Draw(hBrocks_[Map[y][x] - 100]);
				break;
			}
			case 101:
			{
				t.position_ = { x,-y,0 };
				Model::SetTransform(hBrocks_[Map[y][x] - 100], t);
				Model::Draw(hBrocks_[Map[y][x] - 100]);
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
