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
    void SpawnEnemy();
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
    TSubclassOf<class AItemBox> SpawnActor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
    TSubclassOf<AActor> SpawnPointClass;

    // ─── 스폰 위치 목록 ───────────────────────────────
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
    TArray<FVector> SpawnLocations;

    // ─── 생성 간격 ────────────────────────────────────
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
    float SpawnInterval = 3.0f;

    FTimerHandle SpawnTimer;
    // 스폰 함수
    void SpawnActors();

protected:
    FTimerHandle SpawnHandle;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
    TSubclassOf<class AAIEnemy> EnemyClass;
    int EnemyCnt;
    UPROPERTY(BlueprintReadOnly, Category = "Game")
    float GameTime = 600.0f; // 10분 = 600초
    FTimerHandle GameTimerHandle;
    void GamePlay();
    void GameOver();

    FTimerHandle StartHandle;
    // 게임 상태를 저장할 변수도 UPROPERTY로 관리하는 것이 좋습니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
    EGameState CurrentState;

};