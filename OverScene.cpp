#include "OverScene.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "Engine/Sprite.h"

OverScene::OverScene(GameObject* parent)
	:GameObject(parent, "OverScene")
{
}

void OverScene::Initialize()
{
}

void OverScene::Update()
{
}

void OverScene::Draw()
{
}

void OverScene::Release()
{
	SAFE_DELETE(sprite_);
}
