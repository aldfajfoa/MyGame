#include "OverScene.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "Engine/Sprite.h"

OverScene::OverScene(GameObject* parent)
	:GameObject(parent, "OverScene")
{
	sprite_ = new Sprite;
	hImage_ = sprite_->Load("OVER.png");
	assert(hImage_ >= 0);
}

void OverScene::Update()
{
	if (Input::IsKey(DIK_T))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TITLE);
	}
}

void OverScene::Draw()
{
	RECT r = { 0,0,IMAGE_SIZE.w,IMAGE_SIZE.h };
	sprite_->Draw(transform_, r, 1);
}

void OverScene::Release()
{
	SAFE_DELETE(sprite_);
}
