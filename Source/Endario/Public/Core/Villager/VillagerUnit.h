// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "VillagerUnit.generated.h"

// Circular Dependency Prevention
class UVillagerComponent;
class UInventoryComponent;
class UProfessionComponent;

UCLASS()
class ENDARIO_API AVillagerUnit : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AVillagerUnit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Circular Dependency Prevention
	UPROPERTY(Category = "Actions Component", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UVillagerComponent* Actions;

	UPROPERTY(Category = "Inventory Component", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UInventoryComponent* Inventory;

	UPROPERTY(Category = "Selection Component", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USelectionComponent* Selection;

	UPROPERTY(Category = "Profession Component", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UProfessionComponent* Profession;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input

	// Attributes
protected:

	/**  Collision sphere and root component */
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Root Mesh")
	class USphereComponent* CollisionSphere;

	UPROPERTY(Category = "Unit Selection", BlueprintReadonly)
	bool bIsSelected;

	// Details
	UPROPERTY(Category = "Unit Details", BlueprintReadonly, VisibleAnywhere)
	FString FirstName; // Just F Strings due to Male vs Female Names...

	UPROPERTY(Category = "Unit Details", BlueprintReadonly, VisibleAnywhere)
	FString LastName; // Just F Strings due to Male vs Female Names...

	UPROPERTY(Category = "Unit Details", BlueprintReadonly, VisibleAnywhere)
	EEndlingGender Gender;

	UPROPERTY(Category = "Unit Details", BlueprintReadonly, VisibleAnywhere)
	EEndlingClass Class;

	// Status Bars
	UPROPERTY(Category = "Unit Status", BlueprintReadonly, VisibleAnywhere)
	float EnergyMax;

	UPROPERTY(Category = "Unit Status", BlueprintReadonly, VisibleAnywhere)
	float EnergyCurrent;

	UPROPERTY(Category = "Unit Status", BlueprintReadonly, VisibleAnywhere)
	float HealthCurrent;

	UPROPERTY(Category = "Unit Status", BlueprintReadonly, VisibleAnywhere)
	float HealthMax;

	UPROPERTY(Category = "Unit Status", BlueprintReadonly, VisibleAnywhere)
	float ExperienceCurrent;

	UPROPERTY(Category = "Unit Status", BlueprintReadonly, VisibleAnywhere)
	float ExperienceMax;

	UPROPERTY(Category = "Unit Status", BlueprintReadonly, VisibleAnywhere)
	int ExperienceLevel;

	UPROPERTY(Category = "Unit Details", BlueprintReadonly, VisibleAnywhere)
	TArray<int32> Ocean;

public:

	// Temporary Static Mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* BaseMesh;

	// Temporary Static Mesh
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StatusMesh;

	// Inits
	UFUNCTION(BlueprintCallable, Category = "Villager Details")
	TArray<int> InitOceanDetails();

	// Getters
	UFUNCTION(BlueprintCallable, Category = "Villager Details")
	virtual FString GetFirstName();

	UFUNCTION(BlueprintCallable, Category = "Villager Details")
	virtual FString GetLastName();

	UFUNCTION(BlueprintCallable, Category = "Villager Details")
	EEndlingGender GetGender();

	UFUNCTION(BlueprintCallable, Category = "Villager Details")
	EEndlingClass GetClass();

	UFUNCTION(BlueprintCallable, Category = "Villager Details")
	virtual TArray<int32> GetOcean();

	UFUNCTION(BlueprintCallable, Category = "Unit Status")
	float GetEnergyMax();

	UFUNCTION(BlueprintCallable, Category = "Unit Status")
	float GetEnergyCurrent();

	UFUNCTION(BlueprintCallable, Category = "Unit Status")
	float GetHealthMax();

	UFUNCTION(BlueprintCallable, Category = "Unit Status")
	float GetHealthCurrent();

	UFUNCTION(BlueprintCallable, Category = "Unit Status")
	float GetExperienceMax();

	UFUNCTION(BlueprintCallable, Category = "Unit Status")
	float GetExperienceCurrent();

	UFUNCTION(BlueprintCallable, Category = "Unit Status")
	int GetExperienceLevel();

	// Setters
	UFUNCTION(BlueprintCallable, Category = "Villager Details")
	void SetProfession( EEndlingClass ERequestedClass );

	// Utility
	UFUNCTION(BlueprintCallable, Category = "Unit Status")
	void UpdateHealth(float RequestedChange);

	UFUNCTION(BlueprintCallable, Category = "Unit Status")
	void UpdateEnergy(float RequestedChange);

	UFUNCTION(BlueprintCallable, Category = "Unit Status")
	void UpdateLevel(int RequestedChange);
};
