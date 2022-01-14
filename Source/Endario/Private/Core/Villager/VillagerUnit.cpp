// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/Villager/VillagerUnit.h"
//#include "FunctionLibrary.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "Core/Villager/VillagerComponent.h"
#include "Core/Inventory/InventoryComponent.h"

#include "Core/Villager/Professions/HarvesterComponent.h"
#include "Core/Villager/Professions/ProfessionComponent.h"

#include "Core/SelectionUI/SelectionComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <time.h>

// Function For Enum Conversion...
const FString EnumToString(const TCHAR* Enum, int32 EnumValue)
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, Enum, true);
	if (!EnumPtr)
		return NSLOCTEXT("Invalid", "Invalid", "Invalid").ToString();

#if WITH_EDITOR
	return EnumPtr->GetValueAsString(EnumValue);
#else
	return EnumPtr->GetEnumName(EnumValue);
#endif
}

AVillagerUnit::AVillagerUnit() {

	PrimaryActorTick.bCanEverTick = true;

	// Set Root Component and also set root comp's size.
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	SetRootComponent(CapsuleComponent);
	CollisionSphere->InitSphereRadius(32.0);
	CollisionSphere->SetWorldScale3D(FVector(0.25, 0.25, 0.25));

	CollisionSphere->SetCollisionProfileName(TEXT("IgnoreOnlyPawn"));
	this->GetCapsuleComponent()->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
	this->GetCapsuleComponent()->SetCollisionProfileName(TEXT("VillagerPassThrough"));
	this->GetCapsuleComponent()->SetCapsuleHalfHeight(50.0f);

	this->GetCapsuleComponent()->SetAbsolute()

	// More Temporary Mesh Things
	BaseMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Villager Base Mesh"));
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Villager Base Mesh"));
	SetRootComponent(BaseMesh);

	float capHeight = this->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();

	// Find and Assign Mesh
	auto MeshAsset = ConstructorHelpers::FObjectFinder<USkeletalMesh>(TEXT("SkeletalMesh'/Game/Models/Villagers/Initial/VillagerInitialWalking.VillagerInitialWalking'"));
	if (MeshAsset.Object != nullptr)
	{
		BaseMesh->SetSkeletalMesh(MeshAsset.Object);
		BaseMesh->SetWorldScale3D(FVector(0.3f, 0.3f, 0.3f));
		BaseMesh->SetupAttachment(GetCapsuleComponent());
		BaseMesh->SetRelativeLocation(FVector(0.0f, 00.0f, -capHeight));
		BaseMesh->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	}

	SelectionComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Villager Selection Mesh"));

	// Find and Assign Mesh
	if (MeshAsset2.Object != nullptr)	{
		SelectionMesh->SetStaticMesh(MeshAsset2.Object);
		SelectionMesh->SetupAttachment(BaseMesh);
	}

	StatusMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Villager Status Mesh"));

	// Find and Assign Mesh
	auto MeshAsset3 = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Models/Decals/StatusCone.StatusCone'"));
	if (MeshAsset3.Object != nullptr)
	{
		StatusMesh->SetWorldScale3D(FVector(0.01f, 0.01f, 0.01f));
		StatusMesh->SetStaticMesh(MeshAsset3.Object);
		StatusMesh->SetupAttachment(BaseMesh);

		StatusMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 56.0f));
		StatusMesh->ComponentTags.Add(FName("StatusMesh"));;

		StatusMesh->SetVisibility(false);
	}

	// StatusMesh
	this->bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 100.0f, 0.0f);

	// Connect AI Controller
	auto CustomAIController = ConstructorHelpers::FObjectFinder<AController>(TEXT("Blueprint'/Game/Core/DebugAndTest/TEST_AIController.TEST_AIController'"));

	static ConstructorHelpers::FObjectFinder<UBlueprint> AICon(TEXT("Blueprint'/Game/Core/DebugAndTest/AI/TEST_UnitAIController.TEST_UnitAIController'"));
	AIControllerClass = AICon.Object->GeneratedClass;
	Gender = EEndlingGender::Male;

	if (Gender == EEndlingGender::Male) {
		UE_LOG(LogTemp, Warning, TEXT("Gender Male"));

		FirstName = UEnum::GetValueAsString( static_cast<EEndlingMaleFirstName>(FMath::RandRange(0, 25)) ).RightChop(23);
		LastName = UEnum::GetValueAsString( static_cast<EEndlingMaleLastName>(FMath::RandRange(0, 25)) ).RightChop(22);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Gender Female"));

		FirstName = StaticEnum<EEndlingFemaleFirstName>()->GetValueAsString(static_cast<EEndlingFemaleFirstName>(FMath::RandRange(0, 25))).RightChop(25);
		LastName = StaticEnum<EEndlingFemaleLastName>()->GetValueAsString(static_cast<EEndlingFemaleLastName>(FMath::RandRange(0, 25))).RightChop(24);
	}

	// Class and Ocean Traits
	Class = EEndlingClass::Unassigned;
	Ocean = InitOceanDetails();

	// Status Bars
	EnergyMax = 100.0f;
	EnergyCurrent = 100.0f;
	HealthCurrent = 100.0f;
	HealthMax = 100.0f;
	ExperienceCurrent = 0.0f;
	ExperienceMax = 100.0f;
	ExperienceLevel = 1;

	// Attach Villager Component
	Actions = CreateDefaultSubobject<UVillagerComponent>(TEXT("LeadVillagerActionsComponent"));
	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
	Selection = CreateDefaultSubobject<USelectionComponent>(TEXT("Selection"));
	Profession = CreateDefaultSubobject<UProfessionComponent>(TEXT("Profession"));

	Inventory->InitInventory(4, 10);
	Selection->InitSelection(EEndlingType::Unit, EEndlingSelectionSize::Character);
	Selection->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));

	// Widget Stuff
	static ConstructorHelpers::FClassFinder<UUserWidget>UnitStatus(TEXT("WidgetBlueprint'/Game/Widgets/StatusVillager.StatusVillager'"));
	static ConstructorHelpers::FClassFinder<UUserWidget>UnitStatus(TEXT("WidgetBlueprint'/Game/Widgets/StatusVillagerTemp.StatusVillagerTemp'"));
	//if (!ensure(UnitStatus.Class != nullptr)) {
		//UE_LOG(LogTemp, Warning, TEXT("No Widget as class is null"));
	//}

	Status = CreateDefaultSubobject<UWidgetComponent>(TEXT("Status"));

	Status->SetWidgetClass(UnitStatus.Class);
	Status->SetVisibility(true);
	Status->SetupAttachment(BaseMesh);
	Status->SetRelativeLocation(FVector(0.0f, 0.0f, 800.0f));
	Status->SetRelativeScale3D(FVector(0.01f, 0.001f, 0.01f));

	Status->SetWidgetSpace(EWidgetSpace::Screen);
	Status->SetDrawSize(FVector2D(120, 12));

	WidgetBlueprint'/Game/Widgets/StatusVillager.StatusVillager'
	Sets default values
	ASelectableActor::ASelectableActor() {
		MyWidget = CreateDefaultSubobject<UWidgetComponent>("Widget");
		static ConstructorHelpers::FClassFinder<UUserWidget> hudWidgetObj(TEXT("/Game/HUD/SelectableActorHUD_Widget"));
		if (hudWidgetObj.Succeeded()) {
			hudWidgetClass = hudWidgetObj.Class;
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "SelectableActorHUD not found !");
			hudWidgetClass = nullptr;
		}
		MyWidget->SetWidgetSpace(EWidgetSpace::World);
		MyWidget->SetWidgetClass(hudWidgetClass);
		MyWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		MyWidget->SetDrawSize(FVector2D(100.0f, 20.0f));
		MyWidget->SetVisibility(true);
		MyWidget->RegisterComponent();
	}

	StatusVillagerWidgetClass = UnitStatus.Class;
	Status = CreateWidget<UUserWidget>(GetOwner(), StatusVillagerWidgetClass);
	Status = CreateWidget<UUserWidget>(this, StatusVillagerWidgetClass);
}

// Called when the game starts or when spawned
void AVillagerUnit::BeginPlay() {
	Super::BeginPlay();
}

// Called every frame
void AVillagerUnit::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
// void AVillagerUnit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
// {
// 	Super::SetupPlayerInputComponent(PlayerInputComponent);
//
// }

TArray<int> AVillagerUnit::InitOceanDetails() {

	Ocean = { 0, 1, 2, 3, 4 };

	TArray<float> tempOcean = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };

	float sumOcean = 0.0f;
	bool bBalanceFound = false;
	int32 numTries = 0;

	int32 indexesCorrect = 0;
	int32 balanceCorrect = 0;

	while (!bBalanceFound && numTries < 5) {

		sumOcean = 0;

		for (size_t i = 0; i < 5; i++) {

			// Random values between 0 and 1.
			tempOcean[i] = FMath::RandRange(0.0f, 1.0f);
			sumOcean += tempOcean[i];
		}

		indexesCorrect = 0;
		balanceCorrect = 0;
		for (size_t i = 0; i < 5; i++) {

			// Correctly Modify within range
			tempOcean[i] /= sumOcean;
			tempOcean[i] *= 25;

			Ocean[i] = FMath::RoundHalfFromZero(tempOcean[i]);

			if (tempOcean[i] < 10.0f) {
				indexesCorrect += 1;
			}
			balanceCorrect += Ocean[i];

		}

		if (indexesCorrect >= 5) {
			bBalanceFound = true;
		}
		else {
			numTries += 1;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Created Pawn with Ocean Algo %d tries"), numTries);
	UE_LOG(LogTemp, Warning, TEXT("Cur %d, %d, %d, %d, %d = %d"), Ocean[0], Ocean[1], Ocean[2], Ocean[3], Ocean[4], balanceCorrect);

	// Add Sifting if necessary TODO: More sifting will occur at top due using < not <=.... Perhaps shuffle array order?
	if (balanceCorrect < 25) {
		UE_LOG(LogTemp, Warning, TEXT("Sifting for UnderBalance"));
		int32 remainderSift = 25 - balanceCorrect;
		int32 lowestValue;
		int32 lowestIndex = 4;

		for (size_t i = 0; i < remainderSift; i++) {

			lowestValue = 100;
			lowestIndex = 4;
			for (size_t j = 0; j < 5; j++) {
				if (Ocean[j] < lowestValue) {
					lowestValue = Ocean[j];
					lowestIndex = j;
				}
			}
			Ocean[lowestIndex] += 1;
		}

	}
	else if (balanceCorrect > 25) {
		UE_LOG(LogTemp, Warning, TEXT("Sifting for OverBalance"));
		int32 remainderSift = balanceCorrect - 25;
		int32 highestValue;
		int32 highestIndex = 4;

		for (size_t i = 0; i < remainderSift; i++) {

			highestValue = -5;
			highestIndex = 4;
			for (size_t j = 0; j < 5; j++) {
				if (Ocean[j] > highestValue) {
					highestValue = Ocean[j];
					highestIndex = j;
				}
			}
			Ocean[highestIndex] -= 1;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Aft %d, %d, %d, %d, %d"), Ocean[0], Ocean[1], Ocean[2], Ocean[3], Ocean[4]);
	return Ocean;
}

//
//FUnitDetails AVillagerUnit::GetStats() {
//
//
//	// UE_LOG(LogTemp, Warning, TEXT("Attempting to get stats: Pawn"));
//	FUnitDetails CurrentDetails;
//	//srand(time(NULL));
//
//
//	CurrentDetails.UnitName = Name;
//	CurrentDetails.UnitGender = Sex;
//	CurrentDetails.UnitMood = Mood;
//	CurrentDetails.UnitClass = Class;
//	CurrentDetails.UnitStrength = Strength;
//
//	CurrentDetails.UnitOcean = Ocean;
//
//	//SelectionMesh->SetVisibility(true);
//	//CurrentDetails.UnitClass = iSecret;
//	 //UE_LOG(LogTemp, Warning, TEXT("Attempting to get stats: [%s]"), *FString(iSecret) );
//
//	//CurrentDetails.UnitName = "David Temp";
//	//CurrentDetails.UnitGender = "Woman Temp";
//	//CurrentDetails.UnitMood = "Hungry Temp";
//	//CurrentDetails.UnitClass = "Class Temp";
//	//CurrentDetails.UnitTemp = "Temp Temp";
//	//CurrentDetails.UnitClass = iSecret;
//
//	//UE_LOG(LogTemp, Warning, TEXT("Unit Details: %s, %s, %s, %s, %d"), *FString(CurrentDetails.UnitName), *FString(CurrentDetails.UnitGender), *FString(CurrentDetails.UnitMood), *FString(CurrentDetails.UnitClass), CurrentDetails.UnitStrength);
//
//
//	return CurrentDetails;
//}

FString AVillagerUnit::GetFirstName() {

	return FirstName;
}

FString AVillagerUnit::GetLastName() {

	return LastName;
}

EEndlingGender AVillagerUnit::GetGender() {

	return Gender;
}

EEndlingClass AVillagerUnit::GetClass() {

	return Class;
}

TArray<int32> AVillagerUnit::GetOcean() {

	return Ocean;
}

float AVillagerUnit::GetEnergyMax() {

	return EnergyMax;
}

float AVillagerUnit::GetEnergyCurrent() {

	return EnergyCurrent;
}

float AVillagerUnit::GetHealthMax() {

	return HealthMax;
}

float AVillagerUnit::GetHealthCurrent() {

	return HealthCurrent;
}

float AVillagerUnit::GetExperienceMax() {

	return ExperienceMax;
}

float AVillagerUnit::GetExperienceCurrent() {

	return ExperienceCurrent;
}

int AVillagerUnit::GetExperienceLevel() {

	return ExperienceLevel;
}

// Setters
void AVillagerUnit::SetProfession(EEndlingClass ERequestedClass) {

	Class = ERequestedClass;

	//if (Class == EEndlingClass::Lumberjack ||
	//	Class == EEndlingClass::Miner ||
	//	Class == EEndlingClass::Gatherer) {

	//	UE_LOG(LogTemp, Warning, TEXT("Class is a Gatherer"));
	//}
	//else if (Class == EEndlingClass::Woodworker ||
	//	Class == EEndlingClass::Stonemason ||
	//	Class == EEndlingClass::Cook) {

	//	UE_LOG(LogTemp, Warning, TEXT("Class is a Harvester"));
	//}
	//else {

	//}

	Profession->SetVillagerClassInfo(ERequestedClass);
}


// Utility
void AVillagerUnit::UpdateHealth(float RequestedChange) {

	if (RequestedChange > 0.0f) {
		HealthCurrent = FMath::Min(HealthMax, HealthCurrent + RequestedChange);
	}
	else {
		HealthCurrent = FMath::Max(0.0f, HealthCurrent + RequestedChange);
	}
}

void AVillagerUnit::UpdateEnergy(float RequestedChange) {

	if (RequestedChange > 0.0f) {
		EnergyCurrent = FMath::Min(EnergyMax, EnergyCurrent + RequestedChange);
	}
	else {
		EnergyCurrent = FMath::Max(0.0f, EnergyCurrent + RequestedChange);
	}
}

void AVillagerUnit::UpdateLevel(int RequestedChange) {

	if (RequestedChange > 0) {
		ExperienceLevel = FMath::Min(5, ExperienceLevel + RequestedChange);
	}
	else {
		ExperienceLevel = FMath::Max(1, ExperienceLevel + RequestedChange);
	}
}
