// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Core/Enums/EndlingDetails/IncludeEndlingEnums.h"
#include "Core/Villager/VillagerUnit.h"
//#include "Core/Units/VillagerUnitBP.VillagerUnitBP"
//Blueprint'/Game/Core/Units/VillagerUnitBP.VillagerUnitBP'
#include "SelectionComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ENDARIO_API USelectionComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:

	USelectionComponent();
//
protected:

	UPROPERTY(Category = "Endling Selection", BlueprintReadonly)
	AActor* OwningActor;
	
	UPROPERTY(Category = "Endling Selection", BlueprintReadonly)
	bool bIsSelected;


	UPROPERTY(Category = "Endling Selection", BlueprintReadonly)
	EEndlingType EOwnerType;


	UPROPERTY(Category = "Endling Selection", BlueprintReadonly)
	EEndlingSelectionSize EOwnerSize;
	

	UPROPERTY(Category = "Endling Material", BlueprintReadonly)
	UMaterial* MaterialRefCharacter;

	UPROPERTY(Category = "Endling Material", BlueprintReadonly)
	UMaterial* MaterialRefSmallBuilding;

	UPROPERTY(Category = "Endling Material", BlueprintReadonly)
	UMaterial* MaterialRefMediumBuilding;

	UPROPERTY(Category = "Endling Material", BlueprintReadonly)
	UMaterial* MaterialRefLargeBuilding;

	UPROPERTY(Category = "Endling Material", BlueprintReadonly)
	UMaterial* MaterialRefSmallResource;

	UPROPERTY(Category = "Endling Material", BlueprintReadonly)
	UMaterial* MaterialRefMediumResource;

public:

	// Inits
	UFUNCTION(BlueprintCallable, Category = "Endling Selection Setup")
	void InitSelection(EEndlingType ERequestedEndlingType, EEndlingSelectionSize ERequestedSelectionSize);


	// Getters
	UFUNCTION(BlueprintCallable, Category = "Endling Selection")
	bool GetSelection();

	UFUNCTION(BlueprintCallable, Category = "Endling Selection")
	EEndlingType GetEndlingType();

	// Return For Unit Types
	UFUNCTION(BlueprintCallable, Category = "Endling Details")
	virtual FEndlingUnitDetails GetEndlingUnitInfomation();

	UFUNCTION(BlueprintCallable, Category = "Endling Details")
	virtual FEndlingResourceDetails GetEndlingResourceInfomation();

	UFUNCTION(BlueprintCallable, Category = "Endling Details")
	virtual FEndlingBuildingDetails GetEndlingBuildingInfomation();


	// Utility
	UFUNCTION(BlueprintCallable, Category = "Endling Selection")
	void ToggleSelection(bool bNewSelected);
};
