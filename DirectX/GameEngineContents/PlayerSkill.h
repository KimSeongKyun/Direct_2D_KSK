#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� :

enum class SkillList
{
	None,
	MagicBolt,
};
class PlayerSkill :public GameEngineActor
{
public:
	// constrcuter destructer
	PlayerSkill();
	~PlayerSkill();

	// delete Function
	PlayerSkill(const PlayerSkill& _Other) = delete;
	PlayerSkill(PlayerSkill&& _Other) noexcept = delete;
	PlayerSkill& operator=(const PlayerSkill& _Other) = delete;
	PlayerSkill& operator=(PlayerSkill&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;
	void LevelChangeStart() override;


private:
	void ComponentSetting();

	std::shared_ptr<class GameEngineSpriteRenderer> SkillRenderer0;
	std::shared_ptr<class GameEngineSpriteRenderer> SkillRenderer1;
	std::shared_ptr<class GameEngineCollision> ColSkill;

	float TickTime = 0.0f;
	float Speed = 500.0f;

	float4 MagicBoltScale = { 45.0f, 45.0f, 1.0f };
	SkillList CurSkill;
	bool DirectionSet = true;
	int CurPlayerDirection = 0;

public:
	void MagicBoltUpdate(float _Delta);
	void MagicBoltColCheck();
	void SetSkillName(SkillList _Skill);

};	

