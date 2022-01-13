// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
//#include "BehaviorTree/BTTaskNode.h"
//#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
//#include "BehaviorTree/BehaviorTreeTypes.h"
////#include "BehaviorTree/BehaviorTreeComponents.h"
//#include "GameFramework/Pawn.h"

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
	//#include "GameFramework/Pawn.h"
	//#include "BehaviorTree/BehaviorTreeComponent.h"
	//#include "BehaviorTree/BehaviorTreeTypes.h"
	//#include "UObject/UObjectGlobals.h"
#include "TaskCustomInteract.generated.h"


/**
 * 
 */
UCLASS()
class ENDARIO_API UTaskCustomInteract : public UBTTaskNode
{
	GENERATED_BODY()

public:
	// Sets default values for this Tasks's properties
	UTaskCustomInteract(FObjectInitializer const& object_initializer);

	//UFindRandomLocation(FObjectInitializer const& object_initializer);
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory);

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search", meta = (AllowPrivateAccess = "true"))
	float search_radius = 1500.0f;
};