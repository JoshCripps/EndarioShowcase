// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/Villager/Behaviour/Tasks/TaskCustomInteract.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"

UTaskCustomInteract::UTaskCustomInteract(FObjectInitializer const& object_initializer) {
	NodeName = TEXT("Find Random Location");
}

EBTNodeResult::Type UTaskCustomInteract::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory) {

	return EBTNodeResult::Succeeded;
}
