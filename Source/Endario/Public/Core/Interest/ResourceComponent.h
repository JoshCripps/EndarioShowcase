// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Core/Villager/VillagerUnit.h"
#include "ResourceComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ENDARIO_API UResourceComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	// Sets default values for this component's properties
	UResourceComponent();

protected:

	// Called when the game starts
	virtual void BeginPlay() override;

public:

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:

	UPROPERTY(Category = "Resource Varaiables: Resource", VisibleAnywhere, BlueprintReadWrite)
	int ResourceAmount;

	UPROPERTY(Category = "Resource Variables: Villager", VisibleAnywhere, BlueprintReadWrite)
	AVillagerUnit* EngagedVillager;

	// GETTERS
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Resource Villager")
	FORCEINLINE AVillagerUnit* GetResourceVillager() { return EngagedVillager; }

	// SETTERS
	UFUNCTION(BlueprintCallable, Category = "Resource Village")
	virtual void SetResourceVillager(AVillagerUnit* VillagerToEngage);

};
