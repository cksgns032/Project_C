// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h" 
#include "RunGameMode.generated.h"

UENUM(BlueprintType)
enum class EGameState : uint8
{
    Waiting    UMETA(DisplayName = "Waiting"),
    Countdown  UMETA(DisplayName = "Countdown"),
    Playing    UMETA(DisplayName = "Playing"),
    GameOver   UMETA(DisplayName = "GameOver"),
    Clear      UMETA(DisplayName = "Clear")
};

UCLASS()
class CHARACTERMOVE_API ARunGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    //ARunGameMode();

protected:
    // 부모의 StartPlay를 안전하게 오버라이드합니다.
    virtual void StartPlay() override;
    virtual void PostLogin(APlayerController* PC) override;

public:
    UFUNCTION(BlueprintCallable, Category = "Game")
    void SetPlayerInput(bool value);

protected:
    FTimerHandle StartHandle;
    // 게임 상태를 저장할 변수도 UPROPERTY로 관리하는 것이 좋습니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
    EGameState CurrentState;
};