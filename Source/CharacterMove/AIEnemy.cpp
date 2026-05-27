// Fill out your copyright notice in the Description page of Project Settings.


#include "Engine/DamageEvents.h"
#include "RogueCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "AIEnemy.h"

// Sets default values
AAIEnemy::AAIEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAIEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAIEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAIEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
void AAIEnemy::Attack(FVector StartLocation, FVector EndLocation, FVector HalfSize) {
	FHitResult HitResult;
	
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);

	bool hit = UKismetSystemLibrary::BoxTraceSingle(GetWorld(), 
													StartLocation, 
													EndLocation, 
													HalfSize,	
													GetActorRotation(), 
													UEngineTypes::ConvertToTraceType(ECC_Visibility), 
													false, 
													ActorsToIgnore, 
													EDrawDebugTrace::ForDuration, 
													HitResult, 
													true, FLinearColor::Red, FLinearColor::Green, 10);

	if (hit&& HitResult.GetActor())
	{
		UE_LOG(LogTemp, Log, TEXT("Attack"));
		AActor* HitActor = HitResult.GetActor();

		FPointDamageEvent PointDamageEvent;
		PointDamageEvent.HitInfo = HitResult;
		PointDamageEvent.ShotDirection = (EndLocation - StartLocation)
			.GetSafeNormal();

		HitActor->TakeDamage(Damage, PointDamageEvent,GetController(),this);

		ARogueCharacter* HitCharacter = Cast<ARogueCharacter>(HitActor);
		if (HitCharacter)
		{
			// 공격 방향 반대로 계산
			FVector KnockbackDir = (HitResult.GetActor()->GetActorLocation()
				- GetActorLocation());
			KnockbackDir.Z = 0.0f;
			KnockbackDir = KnockbackDir.GetSafeNormal();

			// 뒤로 강하게 밀기

			GEngine->AddOnScreenDebugMessage(
				-1, 2.0f, FColor::Red,
				FString::Printf(
					TEXT("[Knockback] X=%.2f Y=%.2f Z=%.2f"),
					KnockbackDir.X,
					KnockbackDir.Y,
					KnockbackDir.Z)
			);

			HitCharacter->LaunchCharacter(
				KnockbackDir * 2000.0f      // 강한 수평 힘
				+ FVector(0, 0, 800.0f),    // 약간 위로
				true, true
			);
		}
	}
	

}

