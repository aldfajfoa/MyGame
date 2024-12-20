#pragma once
#include "Engine/GameObject.h"
class Player;

class Arrow :
    public GameObject
{
	int hArrow_;
	Player* p;
public:
	Arrow(GameObject* parent);
	~Arrow();

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

