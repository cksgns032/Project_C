// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "WidgetHud.generated.h"

/**
 * 
 */
UCLASS()
class CHARACTERMOVE_API UWidgetHud : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Timer_Text;
	
public:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* Slide_Progress;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* Hook_Progress;

	UFUNCTION(BlueprintCallable)
	void UpdateSlideProgress(float Percent);

	UFUNCTION(BlueprintCallable)
	void UpdateHookProgress(float Percent);

	UFUNCTION(BlueprintCallable)
	void ResetAllProgress();

	void UpdateTimer(float Time);

protected:
	virtual void NativeConstruct() override;
};
