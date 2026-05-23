// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "CableComponent.h"

#include "Hook.h"

// Sets default values
AHook::AHook()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleCollider = CreateDefaultSubobject<USphereComponent>(TEXT("CapsuleCollider"));
	CapsuleCollider->SetupAttachment(RootComponent);

	MeshCom = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshCom"));
	MeshCom->SetupAttachment(CapsuleCollider);

	CableCom = CreateDefaultSubobject<UCableComponent>(TEXT("CableCom"));
	CableCom->SetupAttachment(MeshCom);
}

// Called when the game starts or when spawned
void AHook::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHook::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

