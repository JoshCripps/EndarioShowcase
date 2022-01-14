// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Core/Enums/EndlingDetails/EndlingBuildingType.h"
#include "Core/Enums/EndlingDetails/EndlingBuildingGroup.h"
#include "Core/Enums/Interactions/EndlingBuildingInteractionType.h"
#include "Core/Enums/EndlingDetails/IncludeEndlingEnums.h"
#include "BuildingGeneral.generated.h"


class UInventoryComponent;

UCLASS()
class ENDARIO_API ABuildingGeneral : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABuildingGeneral();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Components
public:

	// Preventing Circular Dependency (2)
	//
	//
	UPROPERTY(Category = "Root Component", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* Root;


	UPROPERTY(Category = "Model Component", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BuildingModel;

	UPROPERTY(Category = "Inventory Component", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UInventoryComponent* Inventory;

	UPROPERTY(Category = "Selection Component", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USelectionComponent* Selection;

protected:

	// Attributes
	UPROPERTY(Category = "Endling Building", BlueprintReadonly)
	EEndlingBuildingType EBuildingType;

	// Attributes
	UPROPERTY(Category = "Endling Building", BlueprintReadonly)
	EEndlingBuildingGroup EBuildingGroup;

	// Attributes
	UPROPERTY(Category = "Endling Building", BlueprintReadonly)
	EEndlingBuildingInteractionType EBuildingInteraction;

public:

	// Getters
	UFUNCTION(Category = "Building Getters", BlueprintCallable)
	FORCEINLINE EEndlingBuildingType GetBuildingType() { return EBuildingType; }

	UFUNCTION(Category = "Building Getters", BlueprintCallable)
	FORCEINLINE EEndlingBuildingGroup GetBuildingGroup() { return EBuildingGroup; }

	UFUNCTION(Category = "Building Getters", BlueprintCallable)
	FORCEINLINE EEndlingBuildingInteractionType GetBuildingInteraction() { return EBuildingInteraction; }

	// Setters
	UFUNCTION(BlueprintCallable, Category = "Building Details")
	void SetBuildingType(EEndlingBuildingType ERequestedType);

	UFUNCTION(BlueprintCallable, Category = "Building Details")
	void SetBuildingInteraction(EEndlingBuildingInteractionType ERequestedInteraction);

};
