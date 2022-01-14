// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include <Endario/Public/Core/Villager/VillagerLead.h>
#include "MainGameInstance.generated.h"

/**
 *
 */
UCLASS()
class ENDARIO_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UMainGameInstance(const FObjectInitializer& ObjectInitializer);

	virtual void Init();

	UFUNCTION(BlueprintCallable)
	void ToggleWidget(bool bNewToggleWidget);
	//AVillagerLead* ShowWidget(AVillagerLead* VillagerRef);

	UPROPERTY(Category = UserInterface, EditAnywhere, BlueprintReadWrite)
	FString TextToChange;

	UFUNCTION(BlueprintCallable, Category = "Widget UI")
	UUserWidget* GetUnitInfoWidget();

protected:

	UPROPERTY(Category = "Widget UI", BlueprintReadonly)
	UUserWidget* UnitInfo;


private:
	TSubclassOf<class UUserWidget>UnitInfoWidgetClass;
};
