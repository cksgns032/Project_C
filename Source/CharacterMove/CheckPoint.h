// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SearchableInterface.h"
#include "CheckPoint.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class CHARACTERMOVE_API ACheckPoint : public AActor, public ISearchableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACheckPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* MeshCom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* BoxCollider;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnBegine_Implementation() override;

};
