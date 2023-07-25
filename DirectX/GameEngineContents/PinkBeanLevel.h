#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class PinkBeanLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	PinkBeanLevel();
	~PinkBeanLevel();

	// delete Function
	PinkBeanLevel(const PinkBeanLevel& _Other) = delete;
	PinkBeanLevel(PinkBeanLevel&& _Other) noexcept = delete;
	PinkBeanLevel& operator=(const PinkBeanLevel& _Other) = delete;
	PinkBeanLevel& operator=(PinkBeanLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:
	std::shared_ptr<class PinkBeanMap> Map0 = nullptr;
	std::shared_ptr<class Player> Player0 = nullptr;
	std::shared_ptr<class PinkBeanDummy> PinkBeanDummy0 = nullptr;

	void CameraSetting();
	void CreateObject();
	void ResourceRoad();
};

