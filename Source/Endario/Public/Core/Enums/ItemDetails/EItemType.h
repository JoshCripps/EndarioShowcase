// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EItemType : uint8 {
	Resource = 0       UMETA(DisplayName = "Resource"),
	Refined = 1        UMETA(DisplayName = "Refined"),
	RawFood = 2        UMETA(DisplayName = "RawFood"),
	CookedFood = 3     UMETA(DisplayName = "CookedFood"),
	Tools = 4          UMETA(DisplayName = "Tools"),
	Weapons = 5        UMETA(DisplayName = "Weapons"),
	Clothing = 6       UMETA(DisplayName = "Clothing"),
};
