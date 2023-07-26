#include "PrecompileHeader.h"
#include "PinkBeanLevel.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "PinkBeanMap.h"
#include "Player.h"
#include "PinkBeanDummy.h"
#include "Ariel.h"

PinkBeanLevel::PinkBeanLevel() 
{
}

PinkBeanLevel::~PinkBeanLevel() 
{
}

void PinkBeanLevel::Start()
{
	ResourceRoad();
	CameraSetting();
	CreateObject();
	
	
}
void PinkBeanLevel::Update(float _DeltaTime)
{

}
void PinkBeanLevel::LevelChangeStart()
{
	ResourceRoad();
	CameraSetting();
	CreateObject();
	
}
void PinkBeanLevel::LevelChangeEnd()
{

}

void PinkBeanLevel::CameraSetting()
{
	GetMainCamera()->GetCamTarget()->DepthSettingOff();
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });
}

void PinkBeanLevel::CreateObject()
{
	if (Map0 == nullptr)
	{
		Map0 = CreateActor<PinkBeanMap>();
		Map0->GetTransform()->SetWorldPosition({ 0.0f, 0.0f, 1.0f });


		Player0 = CreateActor<Player>();
		Player0->GetTransform()->SetWorldPosition({ 0.0f, 0.0f, 1.0f });
		Player0->SetColMap("ColPinkBean.png");
		Player0->SetCurMap("PinkBeanMap.png");

		PinkBeanDummy0 = CreateActor<PinkBeanDummy>();
		PinkBeanDummy0->GetTransform()->SetWorldPosition({ 25.0f, -105.0f, 1.0f });

		Ariel0 = CreateActor<Ariel>();
		Ariel0->GetTransform()->SetWorldPosition({ 7.0f, 50.0f, 1.0f });
	}
}

void PinkBeanLevel::ResourceRoad()
{
	// 플레이어 리소스 로드
	if (nullptr == GameEngineSprite::Find("Idle"))
	{
		GameEngineDirectory NewDir;

		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Player");


		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Idle").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Move").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Jump").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Swing0").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Swing1").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Swing2").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Rope").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Ladder").GetFullPath());
	}

	//핑크빈 리로스 로드
	if (nullptr == GameEngineSprite::Find("PinkBeanAttack1Hit"))
	{
		GameEngineDirectory NewDir;

		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Monster");
		NewDir.Move("PinkBean");
		NewDir.Move("PinkBeanAttack");
		NewDir.Move("PinkBeanAttack1");


		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("PinkBeanAttack1Hit").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("PinkBeanAttack1Motion").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("PinkBeanAttak1Effect").GetFullPath());

		NewDir.MoveParent();
		NewDir.Move("PinkBeanAttack2");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("PinkBeanAttack2Hit").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("PinkBeanAttack2Motion").GetFullPath());

		NewDir.MoveParent();
		NewDir.Move("PinkBeanAttack3");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("PinkBeanAttack3Hit").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("PinkBeanAttack3Motion").GetFullPath());

		NewDir.MoveParent();
		NewDir.Move("PinkBeanAttack4");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("PinkBeanAttack4Hit").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("PinkBeanAttack4Motion").GetFullPath());

		NewDir.MoveParent();
		NewDir.MoveParent();

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("PinkBeanMove").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("PinkBeanDie").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("PinkBeanStand").GetFullPath());

	}

	if (nullptr == GameEngineSprite::Find("MagicBoltBall"))
	{
		GameEngineDirectory NewDir;

		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Player");
		NewDir.Move("Skill");
		NewDir.Move("MagicBolt");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("MagicBoltBall").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("MagicBoltEffect").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("PinkBeanMap"))
	{
		GameEngineDirectory NewDir;

		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Map");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("PinkBeanMap").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("PinkBeanSkill1"))
	{
		GameEngineDirectory NewDir;

		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Monster");
		NewDir.Move("PinkBeanDummy");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("PinkBeanSkill1").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("PinkBeanSkill2").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("PinkBeanSkill3").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("PinkBeanSkill4").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("PinkBeanSkill5").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("PinkBeanSkill6").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("PinkBeanSkill7").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("PinkBeanSkill8").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("PinkBeanSkill9").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("PinkBeanSkill10").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("PinkBeanSkill11").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("PinkBeanSkill12").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("PinkBeanStand0").GetFullPath());

	}

	if (nullptr == GameEngineSprite::Find("ArielStand"))
	{
		GameEngineDirectory NewDir;

		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Monster");
		NewDir.Move("Ariel");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("ArielStand").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("ArielDie").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("ArielSkill1").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("ArielSkill2").GetFullPath());

		NewDir.Move("ArielAttack1");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("ArielAttack1Effect").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("ArielAttack1Hit").GetFullPath());

		NewDir.MoveParent();
		NewDir.Move("ArielAttack2");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("ArielAttack2Effect").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("ArielAttack2Hit").GetFullPath());
	}
}