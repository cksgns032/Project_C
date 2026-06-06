// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "WidgetHud.h"
#include "Widget_GameState.h"
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

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UWidget_GameState> GameStateWidgetClass;

    UPROPERTY(BlueprintReadOnly, Category = "UI")
    TObjectPtr<UWidget_GameState> GameStateWidget;

protected:
    virtual void BeginPlay() override;

public:
    void ShowGameState();
	
};
