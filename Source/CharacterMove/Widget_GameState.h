// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/TextBlock.h"

#include "Blueprint/UserWidget.h"
#include "Widget_GameState.generated.h"

/**
 * 
 */
UCLASS()
class CHARACTERMOVE_API UWidget_GameState : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	UTextBlock* GameState_Text;

public:
	void ShowGameStateText();
	
};
