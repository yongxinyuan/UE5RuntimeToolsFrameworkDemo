#include "RuntimeCustomTool.h"

//
// InteractiveToolsFramework
//
#include "InputState.h"
#include "InteractiveTool.h"
#include "InteractiveToolManager.h"
#include "InteractiveToolBuilder.h"
#include "ToolContextInterfaces.h"
#include "BaseBehaviors/BehaviorTargetInterfaces.h"
#include "BaseBehaviors/MultiClickSequenceInputBehavior.h"

bool URuntimeCustomToolBuilder::CanBuildTool(const FToolBuilderState& SceneState) const
{
	return true;
}

UInteractiveTool* URuntimeCustomToolBuilder::BuildTool(const FToolBuilderState& SceneState) const
{
	URuntimeCustomTool* NewTool = NewObject<URuntimeCustomTool>(SceneState.ToolManager);
	return NewTool;
}

URuntimeCustomTool::URuntimeCustomTool()
{

}

void URuntimeCustomTool::Setup()
{
	UE_LOG(LogTemp, Log, TEXT("URuntimeCustomTool::Setup()"));

	UMultiClickSequenceInputBehavior* MouseBehavior = NewObject<UMultiClickSequenceInputBehavior>();
	MouseBehavior->Initialize(this);
	MouseBehavior->Modifiers.RegisterModifier(1, FInputDeviceState::IsShiftKeyDown);
	AddInputBehavior(MouseBehavior);
}

void URuntimeCustomTool::OnTick(float DeltaTime)
{

}

void URuntimeCustomTool::OnBeginSequencePreview(const FInputDeviceRay& ClickPos)
{
	UE_LOG(LogTemp, Log, TEXT("URuntimeCustomTool::OnBeginSequencePreview()"));
}

bool URuntimeCustomTool::CanBeginClickSequence(const FInputDeviceRay& ClickPos)
{
	UE_LOG(LogTemp, Log, TEXT("URuntimeCustomTool::CanBeginClickSequence()"));

	return true;
}

void URuntimeCustomTool::OnBeginClickSequence(const FInputDeviceRay& ClickPos)
{
	UE_LOG(LogTemp, Log, TEXT("URuntimeCustomTool::OnBeginClickSequence()"));
}

void URuntimeCustomTool::OnNextSequencePreview(const FInputDeviceRay& ClickPos)
{
	UE_LOG(LogTemp, Log, TEXT("URuntimeCustomTool::OnNextSequencePreview()"));
}

bool URuntimeCustomTool::OnNextSequenceClick(const FInputDeviceRay& ClickPos)
{
	UE_LOG(LogTemp, Log, TEXT("URuntimeCustomTool::OnNextSequenceClick()"));

	return true;
}

void URuntimeCustomTool::OnTerminateClickSequence()
{
	UE_LOG(LogTemp, Log, TEXT("URuntimeCustomTool::OnTerminateClickSequence()"));
}

bool URuntimeCustomTool::RequestAbortClickSequence()
{
	UE_LOG(LogTemp, Log, TEXT("URuntimeCustomTool::RequestAbortClickSequence()"));

	return false;
}

void URuntimeCustomTool::OnUpdateModifierState(int ModifierID, bool bIsOn)
{
	UE_LOG(LogTemp, Log, TEXT("URuntimeCustomTool::OnUpdateModifierState()"));
}