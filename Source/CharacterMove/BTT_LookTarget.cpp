// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_LookTarget.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTT_LookTarget::UBTT_LookTarget()
{
	NodeName = TEXT("Look Target");
}

EBTNodeResult::Type UBTT_LookTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController) return EBTNodeResult::Failed;

	APawn* AIPawn = AIController->GetPawn();
	if (!AIPawn) return EBTNodeResult::Failed;

	APawn* Target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey()));
	
	if (!Target) return EBTNodeResult::Failed;

	FVector Direction = Target->GetActorLocation()
		- AIPawn->GetActorLocation();
	Direction.Z = 0.0f;
	Direction.Normalize();

	FRotator LookAtRot = Direction.Rotation();
	AIPawn->SetActorRotation(LookAtRot);

	return EBTNodeResult::Succeeded;
}
