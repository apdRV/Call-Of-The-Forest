// Fill out your copyright notice in the Description page of Project Settings.


#include "MobsAIController.h"
#include "Mob.h"

AMobsAIController::AMobsAIController(FObjectInitializer const& ObjectInitializer)
{

}

void AMobsAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    if(AMob* const Mob = Cast<AMob>(InPawn))
    {
        if(UBehaviorTree* const Tree = Mob->GetBehaviourTree())
        {
            UBlackboardComponent* b;
            UseBlackboard(Tree->BlackboardAsset, b);
            Blackboard = b;
            RunBehaviorTree(Tree);
        }
    }
}