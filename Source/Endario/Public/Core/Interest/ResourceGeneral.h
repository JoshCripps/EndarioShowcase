// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"
#include "Core/Enums/EndlingDetails/IncludeEndlingEnums.h"
#include "ResourceGeneral.generated.h"

UCLASS()
class ENDARIO_API AResourceGeneral : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AResourceGeneral();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:

	UPROPERTY(Category = "Root Component", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* Root;

	UPROPERTY(Category = "Model Component", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* BuildingModel;

	UPROPERTY(Category = "Inventory Component", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UInventoryComponent* Inventory;

	UPROPERTY(Category = "Selection Component", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USelectionComponent* Selection;

		UPROPERTY(Category = "Stimuli Source Component", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UAIPerceptionStimuliSourceComponent* StimuliSource;

protected:

	// Attributes
	UPROPERTY(Category = "Endling Selection", BlueprintReadonly)
	EEndlingResourceType EResourceType;

public:

	UPROPERTY(Category = "Resource Details", VisibleAnywhere, BlueprintReadWrite)
	AVillagerUnit* EngagedVillager;

	// GETTERS
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Resource Villager")
	FORCEINLINE AVillagerUnit* GetResourceVillager() { return EngagedVillager; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Resource Villager")
	FORCEINLINE EEndlingResourceType GetResourceType() { return EResourceType; }

	// Setters
	UFUNCTION(BlueprintCallable, Category = "Resource Details")
	void SetResourceType(EEndlingResourceType ERequestedType);

	// SETTERS
	UFUNCTION(BlueprintCallable, Category = "Resource Village")
	virtual void SetResourceVillager(AVillagerUnit* VillagerToEngage);
};
