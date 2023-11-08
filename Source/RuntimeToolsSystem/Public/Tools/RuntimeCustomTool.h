#pragma once

#include "CoreMinimal.h"

//
// InteractiveToolsFramework
//
#include "InputState.h"
#include "InteractiveTool.h"
#include "InteractiveToolBuilder.h"
#include "ToolContextInterfaces.h"
#include "BaseBehaviors/BehaviorTargetInterfaces.h"

#include "RuntimeCustomTool.generated.h"

UCLASS()
class RUNTIMETOOLSSYSTEM_API URuntimeCustomToolBuilder : public UInteractiveToolBuilder
{
	GENERATED_BODY()

public:
	virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;
	virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;
};

/**
 * 自定义测试工具
 */
UCLASS()
class RUNTIMETOOLSSYSTEM_API URuntimeCustomTool : public UInteractiveTool, public IClickSequenceBehaviorTarget
{
	GENERATED_BODY()

public:

	URuntimeCustomTool();

	//
	//
	//
	virtual void Setup() override;

	//
	// IClickSequenceBehaviorTarget
	//
	virtual void OnBeginSequencePreview(const FInputDeviceRay& ClickPos) override;
	virtual bool CanBeginClickSequence(const FInputDeviceRay& ClickPos) override;
	virtual void OnBeginClickSequence(const FInputDeviceRay& ClickPos) override;
	virtual void OnNextSequencePreview(const FInputDeviceRay& ClickPos) override;
	virtual bool OnNextSequenceClick(const FInputDeviceRay& ClickPos) override;
	virtual void OnTerminateClickSequence() override;
	virtual bool RequestAbortClickSequence() override;
	virtual void OnUpdateModifierState(int ModifierID, bool bIsOn) override;


};