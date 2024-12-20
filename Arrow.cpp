#include "Arrow.h"
#include "Player.h"
#include "Engine/Model.h"

Arrow::Arrow(GameObject* parent)
	:GameObject(parent, "Arrow")
{
	hArrow_ = Model::Load("Arrow.fbx");
	assert(hArrow_ >= 0);
}

Arrow::~Arrow()
{
}

void Arrow::Initialize()
{
}

void Arrow::Update()
{
	transform_.position_.x += 0.5;
}

void Arrow::Draw()
{
	Model::SetTransform(hArrow_, transform_);
	Model::Draw(hArrow_);
}

void Arrow::Release()
{
}
