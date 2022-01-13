// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Core/Enums/EndlingDetails/IncludeEndlingEnums.h"
#include "ProfessionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ENDARIO_API UProfessionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UProfessionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


protected:
	// Harvester

	UPROPERTY(Category = "Villager Type", BlueprintReadonly, VisibleAnywhere)
	EEndlingClass EVillagerClass;

	UPROPERTY(Category = "Villager Class Type", BlueprintReadonly, VisibleAnywhere)
	EEndlingClassType EVillagerClassType;

	UPROPERTY(Category = "Villager Profession Details", BlueprintReadonly, VisibleAnywhere)
	EEndlingResourceType EVillagerInterest;

	UPROPERTY(Category = "Villager Profession Details", BlueprintReadonly, VisibleAnywhere)
	EEndlingBuildingType EVillagerBuilding;

	UPROPERTY(Category = "Villager Profession Details", BlueprintReadonly, VisibleAnywhere)
	EEndlingBuildingType EVillagerStorage;

	UPROPERTY(Category = "Villager Profession Details", BlueprintReadonly, VisibleAnywhere)
	EEndlingBuildingType EVillagerSource;

	UPROPERTY(Category = "Villager Profession Items", BlueprintReadonly, VisibleAnywhere)
	FName NameItemInput;

	UPROPERTY(Category = "Villager Profession Items", BlueprintReadonly, VisibleAnywhere)
	FName NameItemOutput;
		
public:

	// Getters
	UFUNCTION(Category = "Villager Getters", BlueprintCallable)
	FORCEINLINE EEndlingClass GetVillagerClass() { return EVillagerClass; }

	UFUNCTION(Category = "Villager Getters", BlueprintCallable)
	FORCEINLINE EEndlingClassType GetVillagerClassType() { return EVillagerClassType; }

	UFUNCTION(Category = "Villager Getters", BlueprintCallable)
	FORCEINLINE EEndlingResourceType GetVillagerInterest() { return EVillagerInterest; }

	UFUNCTION(Category = "Villager Getters", BlueprintCallable)
	FORCEINLINE EEndlingBuildingType GetVillagerBuilding() { return EVillagerBuilding; }

	UFUNCTION(Category = "Villager Getters", BlueprintCallable)
	FORCEINLINE EEndlingBuildingType GetVillagerStorage() { return EVillagerStorage; }

	UFUNCTION(Category = "Villager Getters", BlueprintCallable)
	FORCEINLINE EEndlingBuildingType GetVillagerSource() { return EVillagerSource; }

	UFUNCTION(Category = "Villager Getters", BlueprintCallable)
	FORCEINLINE FName GetVillagerItemInput() { return NameItemInput; }

	UFUNCTION(Category = "Villager Getters", BlueprintCallable)
	FORCEINLINE FName GetVillagerItemOutput() { return NameItemOutput; }


	// Setters
	UFUNCTION(Category = "Villager Setters", BlueprintCallable)
	void SetVillagerClassInfo(EEndlingClass ERequestedClass);
};
