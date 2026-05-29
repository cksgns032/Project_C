// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RogueCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
class UParkourComponent;
class UCapsuleComponent;
class USphereComponent;
class USearchComponent;
class UCableComponent;
class AGameHUD;

struct FInputActionValue;

UCLASS()
class CHARACTERMOVE_API ARogueCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// rope
	
	// input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* DefaultMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* SlideAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* RopeAction;

public:
	// Sets default values for this character's properties
	ARogueCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	AGameHUD* Hud;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// 점프
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Anim/Jump")
	int CurrentJumpCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Anim/Jump")
	bool IsJumpAni;
	int MaxJumpCount = 2;
	
	// 슬라이드
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Anim/Slide")
	bool CanSlide; // 슬라이드를 할 수 있는지
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Anim/Slide")
	bool IsSlide; // 슬라이드를 하고 있는지 
	int CurrentSlideCnt;
	int MaxSlideCnt = 1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Anim/Slide")
	float SlideCoolTime = 3;
	float CurSlideCoolTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim/Slide")
	UAnimMontage* SlideMontage;
	//FTimerHandle SlideTimer;	

	// 로프
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Cable")
	bool IsGetTarget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cable")
	TObjectPtr<class AHook> Hook;
	FVector RopeEndPos;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Cable")
	bool CanRope;
	float CurRopeCoolTime;
	float RopeCoolTime = 1;
	//FTimerHandle RopeTimer;

	// 타격
	FTimerHandle HitStopTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HitStop")
	float HitStopDuration = 0.1f;  // 느려지는 시간
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HitStop")
	float HitStopTimeScale = 0.05f; // 느려지는 정도 (0에 가까울수록 느림)
	void PlayHitStop();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim/Hit")
	UAnimMontage* HitMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anim/Hit")
	bool IsAirbon;


public:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Jump(const FInputActionValue& Value);
	void Landed(const FHitResult& Hit);
	void Slide(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void EndHook();

public:
	UFUNCTION(BlueprintCallable)
	void EndAni();

public:
	void UpdateCheckPoint(FVector PointLocation);
	FVector SpawnLocation;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Search")
	USearchComponent* SearchCom;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Parkour")
	UParkourComponent* ParkourCom;
};
