// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

#include "Kismet/GameplayStatics.h"
#include "RogueCharacter.h"
#include "GameHUD.h"

#include "CheckPoint.h"

// Sets default values
ACheckPoint::ACheckPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	RootComponent = BoxCollider;

	MeshCom = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshCom"));
	MeshCom->SetupAttachment(RootComponent);
	MeshCom->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

// Called when the game starts or when spawned
void ACheckPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACheckPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACheckPoint::OnBegine_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("Check Point"));
	ARogueCharacter* MainChar = Cast<ARogueCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
	if (MainChar == nullptr) return;

	MainChar->UpdateCheckPoint(GetActorLocation());
	BoxCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	APlayerController* PC = Cast<APlayerController>(MainChar->GetController());
	if (PC == nullptr) return;

	AGameHUD* Hud = Cast<AGameHUD>(PC->GetHUD());

	//Hud->HUDWidget

}

