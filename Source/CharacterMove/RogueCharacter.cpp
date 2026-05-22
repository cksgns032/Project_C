// Fill out your copyright notice in the Description page of Project Settings.

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "./ParkourComponent.h"
#include "./SearchComponent.h"

#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "CableComponent.h"

#include "GameFramework/CharacterMovementComponent.h"

#include "RogueCharacter.h"

// Sets default values
ARogueCharacter::ARogueCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CableCom = CreateDefaultSubobject<UCableComponent>(TEXT("CableCom"));
	CableCom->SetupAttachment(RootComponent);

	SearchCom = CreateDefaultSubobject<USearchComponent>(TEXT("SearchCom"));

	ParkourCom = CreateDefaultSubobject<UParkourComponent>(TEXT("ParkourCom"));
}

// Called when the game starts or when spawned
void ARogueCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	CurrentJumpCount = 0;
	IsSlide = false;
	CanSlide = true;
}

// Called every frame
void ARogueCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsShowRope)
	{
		
		FVector TargetLocation = UKismetMathLibrary::InverseTransformLocation(CableCom->GetComponentTransform(), RopeEndPos);//GetActorTransform()
		FVector GoleLocation = UKismetMathLibrary::VInterpTo_Constant(CableCom->EndLocation,
																	  TargetLocation,
																	  1,300);
		CableCom->EndLocation = GoleLocation;

		if (IsGetTarget)
		{
			FVector ForceValue = UKismetMathLibrary::GetDirectionUnitVector(GetActorLocation(), RopeEndPos);
			ForceValue = ForceValue.GetSafeNormal() * 250000.f;
			GetCharacterMovement()->AddForce(ForceValue);
		}
	}

}

// Called to bind functionality to input
void ARogueCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARogueCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ARogueCharacter::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ARogueCharacter::Jump);
		EnhancedInputComponent->BindAction(SlideAction, ETriggerEvent::Triggered, this, &ARogueCharacter::Slide);
		EnhancedInputComponent->BindAction(RopeAction, ETriggerEvent::Started, this, &ARogueCharacter::StartRope);
		EnhancedInputComponent->BindAction(RopeAction, ETriggerEvent::Completed, this, &ARogueCharacter::EndRope);
	}
}

void ARogueCharacter::Move(const FInputActionValue& Value)
{
	if(IsSlide == true)
	{
		return;
	}
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ARogueCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D vector = Value.Get<FVector2D>();

	AddControllerYawInput(vector.X * .5f);
	AddControllerPitchInput(vector.Y * -0.5f);
}

void ARogueCharacter::Jump(const FInputActionValue& Value)
{
	if (IsSlide)
	{
		return;
	}
	if (CurrentJumpCount >= MaxJumpCount)
	{
		return;
	}
	if (GetCharacterMovement()->IsFalling() && CurrentJumpCount == 1)
	{
 		LaunchCharacter(
			FVector(0, 0, GetCharacterMovement()->JumpZVelocity),
			false, true
		);
		CurrentJumpCount++;
	}
	else
	{
		Super::Jump();
		CurrentJumpCount++;
	}

	ParkourCom->TraceLege();

}

void ARogueCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	// 착지 시 초기화
	CurrentJumpCount = 0;
}

void ARogueCharacter::Slide(const FInputActionValue& Value)
{
	if (IsSlide || CanSlide == false)
	{
		return;
	}
	IsSlide = true;
	CanSlide = false;

	// 마찰력 감소 (미끄러지게)
	GetCharacterMovement()->GroundFriction = 0.5f;
	GetCharacterMovement()->BrakingDecelerationWalking = 500.0f;
	GetCharacterMovement()->MaxWalkSpeed = 1500;

	// 현재 전방 방향으로 힘 적용
	FVector SlideDir = GetActorForwardVector();
	LaunchCharacter(
		SlideDir * 1500,
		true, false
	);

	float OriginalHalfHeight = 88.0f;
	float OriginalRadius = 34.0f;
	float SlideHalfHeight = 35.0f;

	// 높이 차이 계산
	float HeightDiff = -90 + (OriginalHalfHeight - SlideHalfHeight);

	// 캡슐 크기 줄이기
	GetCapsuleComponent()->SetCapsuleSize(
		OriginalRadius, SlideHalfHeight);

	// 캡슐이 올라간 만큼 아래로 위치 보정
	GetMesh()->SetRelativeLocation(FVector(0, 0, HeightDiff));

	if (SlideMontage)
	{
		PlayAnimMontage(SlideMontage);
	}

	GetWorld()->GetTimerManager().ClearTimer(SlideTimer);
	GetWorld()->GetTimerManager().SetTimer(SlideTimer, [this]() { CanSlide = true; UE_LOG(LogTemp, Log, TEXT("Clear")); }, SlideCoolTime, false);
}

void ARogueCharacter::StartRope(const FInputActionValue& Value)
{
	IsShowRope = true;

	FVector ViewLocation;
	FRotator ViewRotator;
	GetController()->GetPlayerViewPoint(ViewLocation, ViewRotator);

	FVector StartLocation = GetActorLocation();
	FVector RotatorForward = UKismetMathLibrary::GetForwardVector(ViewRotator);
	FVector EndLocation = (RotatorForward *3000) + ViewLocation;

	FHitResult HitResult;
	IsGetTarget = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility);

	if (IsGetTarget)
	{
		RopeEndPos = HitResult.ImpactPoint;
		GetCapsuleComponent()->SetCapsuleSize(
			88, 88);
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
	}
	else
	{
		RopeEndPos = EndLocation;
	}
	CableCom->SetVisibility(true);
}

void ARogueCharacter::EndRope(const FInputActionValue& Value)
{
	RopeEndPos = FVector::ZeroVector;

	GetCapsuleComponent()->SetCapsuleSize(
		34, 88);

	CableCom->SetVisibility(false);
	CableCom->EndLocation.Set(0,0,0);
	IsGetTarget = false;
	IsShowRope = false;
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Falling);
}

void ARogueCharacter::EndAni()
{
	// Slider에 관한
	IsSlide = false;

	GetCharacterMovement()->GroundFriction = 8.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2048.0f;
	GetCharacterMovement()->MaxWalkSpeed = 600;

	float OriginalHalfHeight = 88.0f;
	float OriginalRadius = 34.0f;

	// 캡슐 크기 복구
	GetCapsuleComponent()->SetCapsuleSize(
		OriginalRadius, OriginalHalfHeight);

	// 메쉬 위치 복구
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));

	FVector CurrentLocation = GetActorLocation();
	FVector SafeLocation = CurrentLocation;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	// 위쪽으로 안전한 위치 탐색
	for (int32 i = 0; i < 30; i++)
	{
		FHitResult Hit;
		FVector TestLocation = CurrentLocation
			+ FVector(0, 0, i * 10.0f);

		bool bBlocked = GetWorld()->SweepSingleByChannel(
			Hit,
			TestLocation,
			TestLocation,
			FQuat::Identity,
			ECC_Visibility,
			FCollisionShape::MakeCapsule(34.0f, 88.0f),
			Params
		);
		UE_LOG(LogTemp, Log, TEXT("%d"), i);
		if (!bBlocked)
		{
			SafeLocation = TestLocation;

			break;
		}
	}

	// 안전한 위치로 이동 후 종료
	SetActorLocation(SafeLocation);

}

