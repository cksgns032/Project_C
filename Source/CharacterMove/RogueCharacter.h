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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Anim/Slide")
	float SlideCoolTime = 3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim/Slide")
	UAnimMontage* SlideMontage;
	FTimerHandle SlideTimer;	

	// 로프
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Cable")
	bool IsGetTarget;
	/*UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Cable")
	bool IsShowRope; */
	FVector RopeEndPos;

public:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Jump(const FInputActionValue& Value);
	void Landed(const FHitResult& Hit);
	void Slide(const FInputActionValue& Value);
	virtual float TakeDamage(float DamageAmount,FDamageEvent const& DamageEvent,AController* EventInstigator,AActor* DamageCauser) override;


public:
	UFUNCTION(BlueprintCallable)
	void EndAni();

public:
	/*UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cable")
	UCableComponent* CableCom;*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Search")
	USearchComponent* SearchCom;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Parkour")
	UParkourComponent* ParkourCom;
};
