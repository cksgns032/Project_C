// Fill out your copyright notice in the Description page of Project Settings.


#include "Engine/DamageEvents.h"
#include "RogueCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
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

	FCollisionQueryParams params;
	params.AddIgnoredActor(this);

	bool hit = GetWorld()->SweepSingleByChannel(HitResult, StartLocation, EndLocation, GetActorQuat(), ECC_Visibility, FCollisionShape::MakeBox(HalfSize), params);

	/*DrawDebugBox(
		GetWorld(),
		StartLocation - EndLocation,
		HalfSize,
		GetActorQuat(),
		FColor::Red,
		false, 5.f
	);*/

	if (hit&& HitResult.GetActor())
	{
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
			HitCharacter->LaunchCharacter(
				KnockbackDir * 2000.0f      // 강한 수평 힘
				+ FVector(0, 0, 800.0f),    // 약간 위로
				true, true
			);
		}
	}
	

}

void AAIEnemy::ThrowAttack(int ProjectileCnt, float Angle)
{
	FVector  StartLocation = GetActorLocation()
		+ GetActorForwardVector() * 100.0f;

	FRotator BaseRotation;

	APawn* TargetActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (TargetActor)
	{
		// 타겟 방향 (높이 차이 포함)
		FVector Direction = (TargetActor->GetActorLocation()
			- StartLocation).GetSafeNormal();

		// Pitch 포함된 회전
		BaseRotation = Direction.Rotation();
	}
	else
	{
		BaseRotation = GetActorRotation();
	}

	// Count 가 1이면 직선 / 2개 이상이면 부채꼴
	float AngleStep = (ProjectileCnt > 1)
		? Angle / (ProjectileCnt - 1)
		: 0.0f;

	float StartAngle = (ProjectileCnt > 1)
		? -Angle / 2.0f
		: 0.0f;  // 1개면 정면

	for (int32 i = 0; i < ProjectileCnt; i++)
	{
		float CurrentAngle = StartAngle + (AngleStep * i);

		FRotator SpawnRotation = BaseRotation;
		SpawnRotation.Yaw += CurrentAngle;

		FVector Direction = SpawnRotation.Vector();
		FVector SpawnLocation = StartLocation
			+ Direction * 50.0f;

		FActorSpawnParameters Params;
		Params.Owner = this;
		Params.Instigator = GetInstigator();
		Params.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		GetWorld()->SpawnActor<AActor>(
			ProjectileClass,
			SpawnLocation,
			SpawnRotation,
			Params
		);
	}
}

