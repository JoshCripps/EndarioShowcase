// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Pawn.h"
#include "VillagerLead.generated.h"

USTRUCT(BlueprintType) struct FUnitDetailsBU {

	GENERATED_BODY()

	UPROPERTY(editAnywhere, BlueprintReadWrite)
	FString UnitName;
	UPROPERTY(editAnywhere, BlueprintReadWrite)
	FString UnitGender;
	UPROPERTY(editAnywhere, BlueprintReadWrite)
	FString UnitClass;
	UPROPERTY(editAnywhere, BlueprintReadWrite)
	FString UnitMood;
	UPROPERTY(editAnywhere, BlueprintReadWrite)
	int32 UnitStrength;
	UPROPERTY(editAnywhere, BlueprintReadWrite)
	TArray<int32> UnitOcean;

	// Default Constructor
	FUnitDetailsBU() {
		UnitName = "Name. Temp";
		UnitGender = "Gender. Temp";
		UnitClass = "Class. Temp";
		UnitMood = "Personality. Temp";
		UnitStrength = 0;
		UnitOcean = { 0, 0, 0, 0, 0 };
	}
};

// Circular Dependency Prevention
class UVillagerComponent;

UCLASS()
class ENDARIO_API AVillagerLead : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AVillagerLead();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// Preventing Circular Dependency (2)
	UPROPERTY(Category = "Actions Component", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UVillagerComponent* VillagerActionsComponent;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Attributes
protected:
	/**  Collision sphere and root component */
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Root Mesh")
	class USphereComponent* CollisionSphere;

	// Details
	UPROPERTY(Category = "Unit Details", BlueprintReadonly)
	FString Name;

	UPROPERTY(Category = "Unit Details", BlueprintReadonly)
	FString Class;

	UPROPERTY(Category = "Unit Details", BlueprintReadonly)
	FString Sex;

	UPROPERTY(Category = "Unit Details", BlueprintReadonly)
	FString Mood;

	UPROPERTY(Category = "Unit Details", BlueprintReadonly)
	int32 Strength;

	UPROPERTY(Category = "Unit Details", BlueprintReadonly)
	TArray<int32> Ocean;

public:

	// Temporary Static Mesh
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	// Temporary Static Mesh
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* SelectionMesh;

	// Inits
	UFUNCTION(BlueprintCallable, Category = "Villager Details")
	TArray<int> InitOceanDetails();

	// Getters
	UFUNCTION(BlueprintCallable, Category = "Villager Details")
	virtual FUnitDetailsBU GetStatsBU();

	UFUNCTION(BlueprintCallable, Category = "Villager Selection")
	void ToggleSelection(bool bIsSelected);

};
