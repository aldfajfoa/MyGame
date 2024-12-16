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
	:GameObject(parent, "Stage"), hModel_(-1)
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

	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			Map[h][w] = csv.GetInt(w, h);
			if (Map[h][w] == 100)
			{
				StageboxColl = new BoxCollider({ (float)w,(float)-h,0 }, { 1.0,1.0,1.0 });
				AddCollider(StageboxColl);
			}
		}
	}

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
}

void Stage::Initialize()
{
	hModel_ = Model::Load("Box.fbx");
	assert(hModel_ >= 0);

	//StageboxColl = new BoxCollider({ 0,0,0 }, { 1.0,1.0,1.0 });
	//AddCollider(StageboxColl);
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
				Model::SetTransform(hModel_, t);
				Model::Draw(hModel_);
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

int Stage::CollisionRight(int x, int y)
{
	if (IsWallBlock(x, y))
	{
		//当たっているので、めり込んだ量を返す
 		return x;
	}
	else
		return 0;
}

int Stage::CollisionLeft(int x, int y)
{
	return 0;
}

int Stage::CollisionDown(int x, int y)
{
	return 0;
}

int Stage::CollisionUp(int x, int y)
{
	return 0;
}

bool Stage::IsWallBlock(int x, int y)
{
	if (x >= 0 || x < width || -y >= 0 || -y < height)
	{
		Player* pplayer = GetParent()->FindGameObject<Player>();
		if (pplayer != nullptr)
		{
			switch (Map[x][-y])
			{
			case 100:
				return true;
			}
			return false;
		}
	}
}