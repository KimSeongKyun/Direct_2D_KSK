#pragma once
#include <GameEngineCore/GameEngineActor.h>


// Ό³Έν :
class Monster :public GameEngineActor
{
public:
	// constrcuter destructer
	Monster();
	~Monster();

	// delete Function
	Monster(const Monster& _Other) = delete;
	Monster(Monster&& _Other) noexcept = delete;
	Monster& operator=(const Monster& _Other) = delete;
	Monster& operator=(Monster&& _Other) noexcept = delete;


	void GravityCheck(float _Delta);

	void SetColMap(const std::string_view _ColMap);
	void SetCurMap(const std::string_view& _ColMap);
	std::shared_ptr<class GameEngineTexture>  GetColMap() { return ColMap; };
	std::shared_ptr<class GameEngineTexture>  GetCurMap() { return CurMap; };
	class GameEnginePixelColor GetGroundColor() { return ColGroundColor; };
	class GameEnginePixelColor GetWallColor() { return ColWallColor; };
	float4 GetMonsterSize();
	void SetMonsterSize(float4 _Size);

	float GetGravity() { return Gravity; };
	void SetGravity(float _value) { Gravity = _value; };
	bool IsGravity() { return GravityOn; }
	void SetHP(int _HP) { HP = _HP; };


	


protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;

private:
	std::shared_ptr<class GameEngineTexture> ColMap;
	std::shared_ptr<class GameEngineTexture> CurMap;

	class GameEnginePixelColor ColGroundColor = { (char)255, (char)0, (char)255,(char)255 };
	class GameEnginePixelColor ColWallColor = { (char)0, (char)255, (char)255,(char)255 };

	float4 MonsterScale;
	float Gravity = 0.0f;
	bool GravityOn = true;

	int HP = 0;


public:
	void Damage(int _Damge);
	
};

