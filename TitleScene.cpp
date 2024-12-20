#include "TitleScene.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "Engine/Sprite.h"

TitleScene::TitleScene(GameObject* parent)
	:GameObject(parent,"TitleScene")
{
	sprite_ = new Sprite;
	hImage_ = sprite_->Load("TITLE.png");
	assert(hImage_ >= 0);
}

//void TitleScene::Initialize(){}

void TitleScene::Update()
{
	if (Input::IsKey(DIK_P))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_PLAY);
	}
}

void TitleScene::Draw()
{
	RECT r = {0,0,IMAGE_SIZE.w,IMAGE_SIZE.h};
	sprite_->Draw(transform_,r,1);
}

void TitleScene::Release()
{
	SAFE_DELETE(sprite_);
}
