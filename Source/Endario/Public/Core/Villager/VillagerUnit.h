// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "VillagerUnit.generated.h"
//
//
//USTRUCT(BlueprintType)
//struct FUnitDetails
//{
//
//	GENERATED_BODY()
//
//		UPROPERTY(editAnywhere, BlueprintReadWrite)
//		FString UnitName;
//	UPROPERTY(editAnywhere, BlueprintReadWrite)
//		FString UnitGender;
//	UPROPERTY(editAnywhere, BlueprintReadWrite)
//		FString UnitClass;
//	UPROPERTY(editAnywhere, BlueprintReadWrite)
//		FString UnitMood;
//	UPROPERTY(editAnywhere, BlueprintReadWrite)
//		int32 UnitStrength;
//	UPROPERTY(editAnywhere, BlueprintReadWrite)
//		TArray<int32> UnitOcean;
//
//	// Default Constructor
//	FUnitDetails() {
//		UnitName = "Name. Temp";
//		UnitGender = "Gender. Temp";
//		UnitClass = "Class. Temp";
//		UnitMood = "Personality. Temp";
//		UnitStrength = 0;
//		UnitOcean = { 0, 0, 0, 0, 0 };
//	}
//
//};

// Preventing Circular Dependency (1)
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


	// Preventing Circular Dependency (2)
	UPROPERTY(Category = "Actions Component", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UVillagerComponent* Actions;

	UPROPERTY(Category = "Inventory Component", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UInventoryComponent* Inventory;

	UPROPERTY(Category = "Selection Component", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USelectionComponent* Selection;

	//UPROPERTY(Category = "Status Component", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	//class UWidgetComponent* Status;

	UPROPERTY(Category = "Profession Component", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UProfessionComponent* Profession;

	//class UActo* Profession;
	//TSubclassOf<class UUserWidget>StatusVillagerWidgetClass;
	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



	// TEMP FOR EVENT DISPTACH
	//UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	//CallDisplayUnitHUD DisplayingHUD;

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

	


	//UPROPERTY(Category = "Unit Details", BlueprintReadonly, VisibleAnywhere)
	//FString Mood;

	//UPROPERTY(Category = "Unit Details", BlueprintReadonly, VisibleAnywhere)
	//int32 Strength;

	UPROPERTY(Category = "Unit Details", BlueprintReadonly, VisibleAnywhere)
	TArray<int32> Ocean;

public:

	// Temporary Static Mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* BaseMesh;

	// Temporary Static Mesh
	//UPROPERTY(VisibleAnywhere)
	//UStaticMeshComponent* SelectionMesh;

	// Temporary Static Mesh
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StatusMesh;

	// Temporary Struct
	//FUnitDetails UnitDetails;

	// Inits
	UFUNCTION(BlueprintCallable, Category = "Villager Details")
	TArray<int> InitOceanDetails();


	// Getters
	//UFUNCTION(BlueprintCallable, Category = "Villager Details")
	//virtual FEndlingUnitDetails GetStats();

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

	


	//UFUNCTION(BlueprintCallable, Category = "Villager Selection")
	//bool GetSelection();


	// Setters
	UFUNCTION(BlueprintCallable, Category = "Villager Details")
	void SetProfession( EEndlingClass ERequestedClass );

	//UFUNCTION(BlueprintCallable, Category = "Villager Selection")
	//void ToggleSelection(bool bNewSelected);

	// Utility
	UFUNCTION(BlueprintCallable, Category = "Unit Status")
	void UpdateHealth(float RequestedChange);

	UFUNCTION(BlueprintCallable, Category = "Unit Status")
	void UpdateEnergy(float RequestedChange);

	UFUNCTION(BlueprintCallable, Category = "Unit Status")
	void UpdateLevel(int RequestedChange);
};
