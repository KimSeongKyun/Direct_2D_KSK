#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class PinkBeanDummy :public GameEngineActor
{
public:
	// constrcuter destructer
	PinkBeanDummy();
	~PinkBeanDummy();

	// delete Function
	PinkBeanDummy(const PinkBeanDummy& _Other) = delete;
	PinkBeanDummy(PinkBeanDummy&& _Other) noexcept = delete;
	PinkBeanDummy& operator=(const PinkBeanDummy& _Other) = delete;
	PinkBeanDummy& operator=(PinkBeanDummy&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta);
	void Render(float _Delta);

private:
	void ComponetSetting();
	void ChangeState(int _StateNum);

	int StateNumber = 0;
	std::string PinkBeanState;
	std::shared_ptr<class GameEngineSpriteRenderer> PinkBeanDummyRender = nullptr;
};

