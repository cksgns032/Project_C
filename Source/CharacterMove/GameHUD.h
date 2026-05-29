// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "WidgetHud.h"
#include "GameHUD.generated.h"

/**
 * 
 */
UCLASS()
class CHARACTERMOVE_API AGameHUD : public AHUD
{
	GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UWidgetHud> HUDWidgetClass;

    UPROPERTY(BlueprintReadOnly, Category = "UI")
    TObjectPtr<UWidgetHud> HUDWidget;

protected:
    virtual void BeginPlay() override;
	
};
