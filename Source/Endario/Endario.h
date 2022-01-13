// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Endario.generated.h"

USTRUCT(BlueprintType)
struct FResourceItem {

	GENERATED_USTRUCT_BODY();

	UPROPERTY(BlueprintReadWrite, Category = Variables)
	FString Name;
	
	// Convert to Enum
	UPROPERTY(BlueprintReadWrite, Category = Variables)
	FString Type;

	//FString Type;

};
