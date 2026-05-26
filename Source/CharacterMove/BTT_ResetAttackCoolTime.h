// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_ResetAttackCoolTime.generated.h"

/**
 * 
 */
UCLASS()
class CHARACTERMOVE_API UBTT_ResetAttackCoolTime : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTT_ResetAttackCoolTime();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	
};
