#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineFSM.h>

// Ό³Έν :


enum class PlayerDirection
{
	Left,
	Right
};

class Player : public GameEngineActor
{
public:
	static Player* MainPlayer;
public:
	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;


protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;
	void LevelChangeStart() override;
	void StateInit();


private:
	GameEngineFSM FSM;

	float Angle = 0.0f;
	float Speed = 100.0f; 
	float Gravity = 0.0f;
	
	bool PlayerGravity = true;

	bool SkillOn = false;

	float SkillTime = 0.0f;
	float MaxSkillTime = 0.0f;
	
	float4 PlayerSize = { 39.0f, 82.0f };
	float4 PlayerHalfValue;
	float4 JumpPower = { 0, 4.5f, 0 };
	float4 CurMapScale;

	std::string CurPlayerState = "Idle";
	
	
	GameEnginePixelColor ColColor = { (char)255, (char)0, (char)255,(char)255 };
	
	std::shared_ptr<class GameEngineTexture> ColMap;
	std::shared_ptr<class GameEngineTexture> CurMap;
	std::shared_ptr<class GameEngineSpriteRenderer> MainRenderer;
	std::shared_ptr<class GameEngineSpriteRenderer> Body;
	std::shared_ptr<class GameEngineCollision> ColRope;
	std::shared_ptr<class GameEngineCollision> ColAttack;
	std::shared_ptr<class PlayerSkill> Skill0;

	

public:
	void RendererStateChange(const std::string _State);
	void TestCallBack();
	void SetColMap(const std::string_view& _ColMap) { ColMap = GameEngineTexture::Find(_ColMap); };
	void SetCurMap(const std::string_view& _ColMap) { CurMap = GameEngineTexture::Find(_ColMap); };
	void SetCurMapScale(float4 _MapScale);
	//void CameraUpdate(float _DeltaTime);
	std::shared_ptr<class GameEngineTexture> GetColMap() { return ColMap; };
	static float4 PlayerPos;

	void GravityCheck(float _DeltaTime);
	void LRColCheck(float _DeltaTime, float4 _LeftOrRight);
	void RopeCheck();

	void Attack();
	void MagicBolt();
};

