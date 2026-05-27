// Fill out your copyright notice in the Description page of Project Settings.

#include "BTT_Attack.h"
#include "./AIEnemy.h"
#include "AIController.h"
#include "BTT_ClearBlackboardValue.h"


UBTT_Attack::UBTT_Attack()
{
}

EBTNodeResult::Type UBTT_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AActor* owner = OwnerComp.GetOwner();
	if (owner == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	AAIEnemy* Enemy = Cast<AAIEnemy>(OwnerComp.GetAIOwner()->GetPawn());

	if (Enemy == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	//Enemy->Attack();

	return EBTNodeResult::Succeeded;
}
