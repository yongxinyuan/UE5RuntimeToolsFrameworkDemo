#include "RuntimeModelingObjectsCreationAPI.h"
#include "InteractiveToolsContext.h"
#include "ContextObjectStore.h"
#include "MeshScene/RuntimeMeshSceneSubsystem.h"

using namespace UE::Geometry;


URuntimeModelingObjectsCreationAPI* URuntimeModelingObjectsCreationAPI::Register(UInteractiveToolsContext* ToolsContext)
{

	UE_LOG(LogTemp, Log, TEXT("URuntimeModelingObjectsCreationAPI::Register()"));
	check(ToolsContext);

	if ( URuntimeModelingObjectsCreationAPI* CreationAPI = ToolsContext->ContextObjectStore->FindContext<URuntimeModelingObjectsCreationAPI>() )
	{
		return CreationAPI;
	}
	auto NewCreationAPI = NewObject<URuntimeModelingObjectsCreationAPI>(ToolsContext);
	ToolsContext->ContextObjectStore->AddContextObject(NewCreationAPI);
	return NewCreationAPI;
}


bool URuntimeModelingObjectsCreationAPI::Deregister(UInteractiveToolsContext* ToolsContext)
{
	UE_LOG(LogTemp, Log, TEXT("URuntimeModelingObjectsCreationAPI::Deregister()"));

	check(ToolsContext);

	if (URuntimeModelingObjectsCreationAPI* FoundAPI = ToolsContext->ContextObjectStore->FindContext<URuntimeModelingObjectsCreationAPI>() )
	{
		ToolsContext->ContextObjectStore->RemoveContextObject(FoundAPI);
		return true;
	}
	return false;
}


FCreateMeshObjectResult URuntimeModelingObjectsCreationAPI::CreateMeshObject(const FCreateMeshObjectParams& CreateMeshParams)
{
	UE_LOG(LogTemp, Log, TEXT("URuntimeModelingObjectsCreationAPI::CreateMeshObject()"));

	// create new SceneObject
	URuntimeMeshSceneObject* SceneObject = URuntimeMeshSceneSubsystem::Get()->CreateNewSceneObject();

	// initialize the mesh, depending on whether we were passed a FMeshDescription or a FDynamicMesh3
	if (CreateMeshParams.MeshType == ECreateMeshObjectSourceMeshType::MeshDescription)
	{
		SceneObject->Initialize(CreateMeshParams.TargetWorld, & CreateMeshParams.MeshDescription.GetValue() );
	}
	else
	{
		SceneObject->Initialize(CreateMeshParams.TargetWorld, & CreateMeshParams.DynamicMesh.GetValue() );
	}

	SceneObject->SetTransform(CreateMeshParams.Transform);

	// return the created Actor/Component
	FCreateMeshObjectResult Result;
	Result.ResultCode = ECreateModelingObjectResult::Ok;
	Result.NewActor = SceneObject->GetActor();
	Result.NewComponent = SceneObject->GetMeshComponent();
	return Result;
}


FCreateTextureObjectResult URuntimeModelingObjectsCreationAPI::CreateTextureObject(const FCreateTextureObjectParams& CreateTexParams)
{
	UE_LOG(LogTemp, Log, TEXT("URuntimeModelingObjectsCreationAPI::CreateTextureObject()"));

	check(false);		// not supported!
	return FCreateTextureObjectResult{ ECreateModelingObjectResult::Failed_InvalidTexture };
}