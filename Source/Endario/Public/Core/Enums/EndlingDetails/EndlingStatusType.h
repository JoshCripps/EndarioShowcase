// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EEndlingStatusType: uint8 {
    Health = 0        UMETA(DisplayName = "Health"),
    Energy = 1        UMETA(DisplayName = "Energy"),
    Experience = 2    UMETA(DisplayName = "Experience"),
    Level = 2         UMETA(DisplayName = "Level"),
};