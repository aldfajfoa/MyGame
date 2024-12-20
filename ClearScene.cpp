#include "ClearScene.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "Engine/Sprite.h"

ClearScene::ClearScene(GameObject* parent)
	:GameObject(parent, "ClearScene")
{
	sprite_ = new Sprite;
	hImage_ = sprite_->Load("CLEAR.png");
	assert(hImage_ >= 0);
}

void ClearScene::Update()
{
	if (Input::IsKey(DIK_T))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TITLE);
	}
}

void ClearScene::Draw()
{
	RECT r = { 0,0,IMAGE_SIZE.w,IMAGE_SIZE.h };
	sprite_->Draw(transform_, r, 1);
}

void ClearScene::Release()
{
	SAFE_DELETE(sprite_);
}
