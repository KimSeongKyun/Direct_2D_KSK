#include "PrecompileHeader.h"
#include "QuickSlot.h"
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineObject.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineUIRenderer.h>

QuickSlot::QuickSlot() 
{
}

QuickSlot::~QuickSlot() 
{
}

void QuickSlot::Start()
{
	std::shared_ptr<GameEngineCamera> Camera = GetLevel()->GetCamera(100);
	Camera->SetProjectionType(CameraType::Orthogonal);
	Camera->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });

	if (nullptr == GameEngineSprite::Find("Quick"))
	{
		GameEngineDirectory NewDir;

		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("UI");


		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Quick").GetFullPath());
	}

	Back = CreateComponent<GameEngineUIRenderer>();
	Back->SetTexture("QuickBack.png");
	Back->SetScaleToTexture("QuickBack.png");

	Cover = CreateComponent<GameEngineUIRenderer>();
	Cover->SetTexture("QuickCover.png");
	Cover->SetScaleToTexture("QuickCover.png");

	float4 CoverScale = Cover->GetTransform()->GetLocalScale();
	Render = CreateComponent<GameEngineUIRenderer>();
	Render-> SetScaleToTexture("QuickButton.png");
	Render-> SetTexture("QuickButton.png");
	Render->GetTransform()->AddLocalPosition({ -CoverScale.hx(), 0.0f , 0.0f });
}

void QuickSlot::Update(float _Delta)
{

}