// Fill out your copyright notice in the Description page of Project Settings.

#include "BTS_CheckDistance.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"

UBTS_CheckDistance::UBTS_CheckDistance()
{
	NodeName = TEXT("Update Attack CoolTime");
}

void UBTS_CheckDistance::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn == nullptr || OwnerComp.GetAIOwner() == nullptr)
	{
		return;
	}
	AActor* OwnerPawn = OwnerComp.GetAIOwner()->GetPawn();
	float Dis = FVector::Distance(OwnerPawn->GetActorLocation(), PlayerPawn->GetActorLocation());
	float CurrentCoolTime = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(GetSelectedBlackboardKey());
	CurrentCoolTime -= DeltaSeconds;
	if (CurrentCoolTime <= 0)
	{
		CurrentCoolTime = 0;
		OwnerComp.GetBlackboardComponent()->SetValueAsBool("bCanAttack", true);
	}
	UE_LOG(LogTemp, Log, TEXT("%f"), CurrentCoolTime);
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(GetSelectedBlackboardKey(), CurrentCoolTime);
}
