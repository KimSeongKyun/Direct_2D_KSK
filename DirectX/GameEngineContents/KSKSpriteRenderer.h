#pragma once
#include <GameEngineCore/GameEngineSpriteRenderer.h>


// ���� :
class KSKSpriteRenderer : public GameEngineSpriteRenderer
{
public:
	void Start() override;

	float4 AColor;

public:
	// constrcuter destructer
	KSKSpriteRenderer();
	~KSKSpriteRenderer();

};
