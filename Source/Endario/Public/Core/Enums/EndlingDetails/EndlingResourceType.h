// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EEndlingResourceType : uint8 {
    Tree = 0    UMETA(DisplayName = "Tree"),
    Cave = 1    UMETA(DisplayName = "Cave"),
    Bush = 2    UMETA(DisplayName = "Bush")
};