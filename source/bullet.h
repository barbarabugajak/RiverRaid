#pragma once
#include "../source/gameObject.h"


class Bullet : public GameObject {

public:

	using GameObject::GameObject;
	
	bool CheckBounds();

	// Happens every game loop
	virtual void Tick(float dt) override;

};
