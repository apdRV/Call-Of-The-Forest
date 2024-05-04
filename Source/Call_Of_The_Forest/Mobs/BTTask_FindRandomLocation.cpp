// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindRandomLocation.h"
#include "NavigationSystem.h"
#include "MobsAIController.h"


UBTTask_FindRandomLocation::UBTTask_FindRandomLocation(FObjectInitializer const& ObjectIniializer)
{
    NodeName = "Find Random Location In NavMesh";
}
EBTNodeResult::Type UBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    // get AI controller and its npc
    if(AMobsAIController* const cont = Cast<AMobsAIController>(OwnerComp.GetAIOwner()))
    {
        if(auto* const mob = cont->GetPawn())
        {
            auto const Origin = mob->GetActorLocation();
            if(auto* const NavSys = UNavigationSystemV1::GetCurrent(GetWorld())){
                FNavLocation Loc;
                if(NavSys->GetRandomPointInNavigableRadius(Origin, SearchRadius, Loc))
                {
                    OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), Loc.Location);
                }
                FinishLatentTask(OwnerComp,  EBTNodeResult::Succeeded);
                return EBTNodeResult::Succeeded;

            }
        }
         

    }
    return EBTNodeResult::Failed;
}