// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Hook.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UCableComponent;

UCLASS()

class CHARACTERMOVE_API AHook : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHook();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* MeshCom;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USphereComponent* CapsuleCollider;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCableComponent* CableCom;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
