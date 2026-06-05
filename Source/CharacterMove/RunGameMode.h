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

// 변수
protected:
    // 아이템 상자
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
    TSubclassOf<class AItemBox> SpawnActor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
    TSubclassOf<AActor> SpawnPointClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
    TArray<FVector> SpawnLocations;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
    float SpawnInterval = 3.0f;

    // 적 
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
    TSubclassOf<class AAIEnemy> EnemyClass;
    
    int EnemyCnt;

    // 게임 상태
    UPROPERTY(BlueprintReadOnly, Category = "Game")
    float GameTime = 600.0f; // 10분 = 600초

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
    EGameState CurrentState;

    int MaxKey = 3;
    int CurKey;

    // Hud
    TObjectPtr<class AGameHUD> GameHud;

// 함수
public:
    UFUNCTION(BlueprintCallable, Category = "Game")
    void SetPlayerInput(bool value);
    void AddKey();
    void UpdateKeyScore();
    void SpawnEnemy();
    void SpawnActors();
    void GamePlay();
    void GameOver();

protected:
    FTimerHandle SpawnHandle; // 적 생성 타이머
    FTimerHandle SpawnTimer;// 상자 생성 타이머
    FTimerHandle GameTimerHandle;// 게임 시간 타이머
    FTimerHandle StartHandle;// 초반 시작 타이머
};