#pragma once
#include "Engine/GameObject.h"
class Sprite;

class OverScene :
    public GameObject
{
	int hImage_;
	Sprite* sprite_;
public:
	OverScene(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

