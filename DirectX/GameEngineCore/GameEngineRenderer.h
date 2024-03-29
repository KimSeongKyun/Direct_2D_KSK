#pragma once
#include "GameEngineComponent.h"
#include "GameEngineShader.h"

class GameEngineRenderUnit 
	: std::enable_shared_from_this<GameEngineRenderUnit>
{
public:
	GameEngineRenderUnit();

public:
	std::shared_ptr<class GameEngineInputLayOut> InputLayOutPtr;
	std::shared_ptr<class GameEngineMesh> Mesh;
	std::shared_ptr<class GameEngineRenderingPipeLine> Pipe;
	GameEngineShaderResHelper ShaderResHelper;

	// 

public:
	void SetMesh(const std::string_view& _Name);
	void SetPipeLine(const std::string_view& _Name);
	void Render(float _DeltaTime);
};

class RenderBaseValue
{
public:
	float4 Time;
	float4 ScreenScale;
	float4 Mouse;
};


// 설명 :
class GameEngineRenderer : public GameEngineComponent
{
	friend class GameEngineCamera;

public:
	// constrcuter destructer
	GameEngineRenderer();
	~GameEngineRenderer();

	// delete Function
	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator=(GameEngineRenderer&& _Other) noexcept = delete;

	// 파이프라인이 세팅되어 있고
	// 어떤 쉐이더를 사용했다는 걸 알아야 하고
	// 그 쉐이더에서 어떤 텍스처를 사용했고
	// 어떤 샘플러 어떤 상수버퍼를 사용했는지를 알아야 한다.
	void SetPipeLine(const std::string_view& _Name, int _index = 0);

	void SetMesh(const std::string_view& _Name, int _index = 0);

	// 여기서 리턴된 파이프라인을 수정하면 이 파이프라인을 사용하는 모든 애들이 바뀌게 된다.
	std::shared_ptr<GameEngineRenderingPipeLine> GetPipeLine(int _index = 0);

	// 이걸 사용하게되면 이 랜더러의 유니트는 자신만의 클론 파이프라인을 가지게 된다.
	std::shared_ptr<GameEngineRenderingPipeLine> GetPipeLineClone(int _index = 0);

	inline GameEngineShaderResHelper& GetShaderResHelper(int _index = 0) 
	{
		return Units[_index]->ShaderResHelper;
	}

	void CameraCullingOn() 
	{
		IsCameraCulling = true;
	}

	void CalSortZ(class GameEngineCamera* _Camera);

	GameEngineCamera* GetCamera() 
	{
		return RenderCamera;
	}

	// 업데이트에서 할것이기 때문에 그냥 하겠습니다. 
	// 랜더 도중에 카메라를 바꾸거나 한다면 이상한 일이 발생할수 있다.

protected:
	void Start();

	void Render(float _Delta) override;

	void PushCameraRender(int _CameraOrder);

private:
	bool IsCameraCulling = false;

	float CalZ = 0.0f;

	GameEngineCamera* RenderCamera;

	std::vector<std::shared_ptr<GameEngineRenderUnit>> Units;

	// Pipe와
	//// GameEngineShaderResHelper 가 합쳐져야 랜더링 이 되는 식이 됩니다.
	//std::shared_ptr<class GameEngineRenderingPipeLine> Pipe;
	//GameEngineShaderResHelper ShaderResHelper;

	RenderBaseValue BaseValue;

	void RenderTransformUpdate(GameEngineCamera* _Camera);
};

