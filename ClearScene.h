#pragma once
#include "Engine/GameObject.h"
class Sprite;

class ClearScene:
	public GameObject
{
	const Size IMAGE_SIZE = { 1280,720 };
	int hImage_;
	Sprite* sprite_;
public:
	ClearScene(GameObject* parent);
	void Initialize() override {};
	void Update() override;
	void Draw() override;
	void Release() override;
};

