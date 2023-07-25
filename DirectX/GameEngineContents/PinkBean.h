#pragma once
#include "Monster.h"

// Ό³Έν :
class PinkBean :public Monster
{
public:
	// constrcuter destructer
	PinkBean();
	~PinkBean();

	// delete Function
	PinkBean(const PinkBean& _Other) = delete;
	PinkBean(PinkBean&& _Other) noexcept = delete;
	PinkBean& operator=(const PinkBean& _Other) = delete;
	PinkBean& operator=(PinkBean&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;

private:
	void ImageResourceLoad();
	bool invincibility = false;

public:
	void Damage(int _Damge) override;
	void SetHP(int _HP) override;
};

