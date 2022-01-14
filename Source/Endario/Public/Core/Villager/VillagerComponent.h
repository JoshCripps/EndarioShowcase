// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Core/Villager/VillagerLead.h"
#include "VillagerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ENDARIO_API UVillagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UVillagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** Get Attached Pawn */
	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite)
	AVillagerLead* VillagerOwner;



public:
	// Methods

	// Getters

	// Setters

	// Utility
	UFUNCTION(BlueprintCallable, Category = "Villager Movement")
	virtual void MoveVillagerTo(float PositionX, float PositionY);

	UFUNCTION(BlueprintCallable, Category = "Villager HUD")
	virtual void CallDisplayUnitHUD(AVillagerLead* HitActor, bool Bypass);
};
