#include "ToolsFrameworkDemoGameModeBase.h"

#include "RuntimeToolsFramework/RuntimeToolsFrameworkSubsystem.h"
#include "MeshScene/RuntimeMeshSceneSubsystem.h"

#include "AddPrimitiveTool.h"
#include "DrawAndRevolveTool.h"
#include "MeshVertexSculptTool.h"
#include "PlaneCutTool.h"

#include "Tools/RuntimeDrawPolygonTool.h"
#include "Tools/RuntimeDynamicMeshSculptTool.h"
#include "Tools/RuntimeRemeshMeshTool.h"
#include "Tools/RuntimeMeshBooleanTool.h"
#include "Tools/RuntimePolyEditTool.h"


AToolsFrameworkDemoGameModeBase::AToolsFrameworkDemoGameModeBase()
{
	UE_LOG(LogTemp, Log, TEXT("AToolsFrameworkDemoGameModeBase::AToolsFrameworkDemoGameModeBase() Prev"));
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
	UE_LOG(LogTemp, Log, TEXT("AToolsFrameworkDemoGameModeBase::AToolsFrameworkDemoGameModeBase() Post"));
}


void AToolsFrameworkDemoGameModeBase::StartPlay()
{
	UE_LOG(LogTemp, Log, TEXT("AToolsFrameworkDemoGameModeBase::StartPlay() Prev"));
	Super::StartPlay();
	InitializeToolsSystem();
	UE_LOG(LogTemp, Log, TEXT("AToolsFrameworkDemoGameModeBase::StartPlay() Post"));
}


void AToolsFrameworkDemoGameModeBase::InitializeToolsSystem()
{
	UE_LOG(LogTemp, Log, TEXT("AToolsFrameworkDemoGameModeBase::InitializeToolsSystem() Prev"));

	UWorld* World = GetWorld();
	UGameInstance* GameInstance = GetGameInstance();
	check(World && GameInstance);

	// create Scene subsystem
	SceneSystem = UGameInstance::GetSubsystem<URuntimeMeshSceneSubsystem>(GameInstance);
	URuntimeMeshSceneSubsystem::InitializeSingleton(SceneSystem);

	// create Tools subsystem
	ToolsSystem = UGameInstance::GetSubsystem<URuntimeToolsFrameworkSubsystem>(GameInstance);
	URuntimeToolsFrameworkSubsystem::InitializeSingleton(ToolsSystem);

	check(SceneSystem && ToolsSystem);

	// initialize Tools and Scene systems
	ToolsSystem->InitializeToolsContext(World);
	SceneSystem->SetCurrentTransactionsAPI(ToolsSystem->GetTransactionsAPI());

	RegisterTools();

	UE_LOG(LogTemp, Log, TEXT("AToolsFrameworkDemoGameModeBase::InitializeToolsSystem() Post"));
}


void AToolsFrameworkDemoGameModeBase::RegisterTools()
{
	UE_LOG(LogTemp, Log, TEXT("AToolsFrameworkDemoGameModeBase::RegisterTools() Prev"));

	UInteractiveToolManager* ToolManager = ToolsSystem->ToolsContext->ToolManager;

	auto AddPrimitiveToolBuilder = NewObject<UAddPrimitiveToolBuilder>();
	AddPrimitiveToolBuilder->ShapeType = UAddPrimitiveToolBuilder::EMakeMeshShapeType::Box;
	ToolManager->RegisterToolType("AddPrimitiveBox", AddPrimitiveToolBuilder);

	auto DrawPolygonToolBuilder = NewObject<URuntimeDrawPolygonToolBuilder>();
	ToolManager->RegisterToolType("DrawPolygon", DrawPolygonToolBuilder);

	auto PolyRevolveToolBuilder = NewObject<UDrawAndRevolveToolBuilder>();
	ToolManager->RegisterToolType("PolyRevolve", PolyRevolveToolBuilder);

	auto PolyEditToolBuilder = NewObject<URuntimePolyEditToolBuilder>();
	ToolManager->RegisterToolType("EditPolygons", PolyEditToolBuilder);

	auto MeshPlaneCutToolBuilder = NewObject<UPlaneCutToolBuilder>();
	ToolManager->RegisterToolType("PlaneCut", MeshPlaneCutToolBuilder);

	auto RemeshMeshToolBuilder = NewObject<URuntimeRemeshMeshToolBuilder>();
	ToolManager->RegisterToolType("RemeshMesh", RemeshMeshToolBuilder);

	auto VertexSculptToolBuilder = NewObject<UMeshVertexSculptToolBuilder>();
	ToolManager->RegisterToolType("VertexSculpt", VertexSculptToolBuilder);

	auto DynaSculptToolBuilder = NewObject<URuntimeDynamicMeshSculptToolBuilder>();
	DynaSculptToolBuilder->bEnableRemeshing = true;
	ToolManager->RegisterToolType("DynaSculpt", DynaSculptToolBuilder);

	auto MeshBooleanToolBuilder = NewObject<URuntimeMeshBooleanToolBuilder>();
	ToolManager->RegisterToolType("MeshBoolean", MeshBooleanToolBuilder);

	UE_LOG(LogTemp, Log, TEXT("AToolsFrameworkDemoGameModeBase::RegisterTools() Post"));
}


void AToolsFrameworkDemoGameModeBase::ShutdownToolsSystem()
{
	UE_LOG(LogTemp, Log, TEXT("AToolsFrameworkDemoGameModeBase::ShutdownToolsSystem() Prev"));

	// TODO: implement this
	check(false);

	UE_LOG(LogTemp, Log, TEXT("AToolsFrameworkDemoGameModeBase::ShutdownToolsSystem() Post"));
}


void AToolsFrameworkDemoGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ToolsSystem)
	{
		ToolsSystem->Tick(DeltaTime);
	}
}



