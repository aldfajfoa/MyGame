#pragma once
#include "Engine/GameObject.h"

class Timer :
    public GameObject
{
	float currentTime_;//Œo‰ßŠÔ‚ğ•Û‚·‚é•Ï”
public:
	Timer(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override {};
	void Release() override;

	bool TimeElapsed(const float& time);//w’è‚µ‚½•b”‚ªŒo‚Á‚½‚çtrue‚ğ•Ô‚·
};

