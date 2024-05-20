
#include "AttackingActor.h"
#include "../Character/MainPaperCharacter.h"
#include "../Mobs/Mob.h"
#include "../Animals/Animal.h"
#include "Math/UnrealMathUtility.h"
#include "../Animals/Predator.h"

void AttackingActor::MakeDamage(AActor* AttackingActor, AActor* AttackedActor)
{
    AMob* Mob = dynamic_cast<AMob*>(AttackingActor);
    APredator* Predator = dynamic_cast<APredator*>(AttackingActor);
    AMainPaperCharacter* MainCharacter = dynamic_cast<AMainPaperCharacter*>(AttackedActor);
    if(MainCharacter != nullptr && Mob != nullptr)
    {
        if((Mob->GetMobState() == EMobState::IdleLeftDown || Mob->GetMobState() == EMobState::LeftDown) && MainCharacter->GetActorLocation().Y <= Mob->GetActorLocation().Y && 
        (Mob->GetActorLocation().Y - MainCharacter->GetActorLocation().Y) <= 30.0f && FMath::Abs(Mob->GetActorLocation().X - MainCharacter->GetActorLocation().X) <= 30.0f)
        {
            Mob->SetMobState(EMobState::AttackLeftDown);
            MainCharacter->Attacked(Mob->GetBaseDamage());
        }
        else if((Mob->GetMobState() == EMobState::IdleRightUp || Mob->GetMobState() == EMobState::RightUp) && MainCharacter->GetActorLocation().Y >= Mob->GetActorLocation().Y && 
        (MainCharacter->GetActorLocation().Y - Mob->GetActorLocation().Y) <= 30.0f && FMath::Abs(Mob->GetActorLocation().X - MainCharacter->GetActorLocation().X) <= 30.0f)
        {
            Mob->SetMobState(EMobState::AttackRightUp);
            MainCharacter->Attacked(Mob->GetBaseDamage());
        }
    }
    // доделать для predator

}