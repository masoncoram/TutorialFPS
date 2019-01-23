// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Classes/AIController.h"
#include "AIController.h"
#include "PatrolRoute.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	// protect against no Patrol Route component

	// protect against empty patrol routes


	// Get the patrol route
	APawn* controlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	UPatrolRoute* PatrolRoute = controlledPawn->FindComponentByClass<UPatrolRoute>();
	if (!ensure(PatrolRoute)) { return EBTNodeResult::Failed; }

	// Get the patrol points
	TArray<AActor*> patrolPoints = PatrolRoute->GetPatrolPoints();
	if (patrolPoints.Num() == 0) {
		UE_LOG(LogTemp, Warning, TEXT("%s missing patrol points"), *(controlledPawn->GetName()));
		return EBTNodeResult::Failed;
	}

	// Set next waypoint
	UBlackboardComponent* blackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = blackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);

	// Cycle Index
	int nextIndex = (Index + 1) % patrolPoints.Num();
	blackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, nextIndex);

	blackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, patrolPoints[Index]);

	UE_LOG(LogTemp, Warning, TEXT("Waypoint index: %i"), Index);
	return EBTNodeResult::Succeeded;
}
