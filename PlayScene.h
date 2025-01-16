#pragma once
#include "Engine/GameObject.h"
class Fbx;
class Stage;

class PlayScene :
    public GameObject
{
private:
	Stage* pField_;
public:
	PlayScene(GameObject* parent);
	~PlayScene();

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

