
#include "AttackingActor.h"
#include "../Character/MainPaperCharacter.h"
#include "../Mobs/Mob.h"
#include "Math/UnrealMathUtility.h"
#include "../Animals/Predator.h"

void AttackingActor::MakeDamage(AActor* AttackingActor, AActor* AttackedActor)
{
    AMob* MobAttacking = dynamic_cast<AMob*>(AttackingActor);
    APredator* PredatorAttacking = dynamic_cast<APredator*>(AttackingActor);
    AMainPaperCharacter* MainCharacterAttacked = dynamic_cast<AMainPaperCharacter*>(AttackedActor);
    if(MainCharacterAttacked != nullptr && MobAttacking != nullptr && !MainCharacterAttacked->GetbIsDead() && !MobAttacking->GetbIsDead())
    {
        if((MobAttacking->GetMobState() == EMobState::IdleLeftDown || MobAttacking->GetMobState() == EMobState::LeftDown || MobAttacking->GetMobState() == EMobState::AttackLeftDown) && MainCharacterAttacked->GetActorLocation().Y <= MobAttacking->GetActorLocation().Y && 
        (MobAttacking->GetActorLocation().Y - MainCharacterAttacked->GetActorLocation().Y) <= 35.0f && FMath::Abs(MobAttacking->GetActorLocation().X - MainCharacterAttacked->GetActorLocation().X) <= 35.0f)
        {
            MobAttacking->SetAttack();
        }
        else if((MobAttacking->GetMobState() == EMobState::IdleRightUp || MobAttacking->GetMobState() == EMobState::RightUp || MobAttacking->GetMobState() == EMobState::AttackRightUp) && MainCharacterAttacked->GetActorLocation().Y >= MobAttacking->GetActorLocation().Y && 
        (MainCharacterAttacked->GetActorLocation().Y - MobAttacking->GetActorLocation().Y) <= 35.0f && FMath::Abs(MobAttacking->GetActorLocation().X - MainCharacterAttacked->GetActorLocation().X) <= 35.0f)
        {
            MobAttacking->SetAttack();
        }
    }
    else if(MainCharacterAttacked != nullptr && PredatorAttacking != nullptr && !MainCharacterAttacked->GetbIsDead() && !PredatorAttacking->GetbIsDead())
    {
        if((PredatorAttacking->GetPredatorState() == EPredatorState::IdleLeftDown || PredatorAttacking->GetPredatorState() == EPredatorState::LeftDown || PredatorAttacking->GetPredatorState() == EPredatorState::AttackingLeftDown) && MainCharacterAttacked->GetActorLocation().Y <= PredatorAttacking->GetActorLocation().Y && 
        (PredatorAttacking->GetActorLocation().Y - MainCharacterAttacked->GetActorLocation().Y) <= 35.0f && FMath::Abs(PredatorAttacking->GetActorLocation().X - MainCharacterAttacked->GetActorLocation().X) <= 35.0f)
        {
            PredatorAttacking->SetAttackAnimation();
        }
        else if((PredatorAttacking->GetPredatorState() == EPredatorState::IdleRightUp || PredatorAttacking->GetPredatorState() == EPredatorState::RightUp || PredatorAttacking->GetPredatorState() == EPredatorState::AttackingRightUp) && MainCharacterAttacked->GetActorLocation().Y >= PredatorAttacking->GetActorLocation().Y && 
        (MainCharacterAttacked->GetActorLocation().Y - PredatorAttacking->GetActorLocation().Y) <= 35.0f && FMath::Abs(PredatorAttacking->GetActorLocation().X - MainCharacterAttacked->GetActorLocation().X) <= 35.0f)
        {
            PredatorAttacking->SetAttackAnimation();
        }
    }
}

void AttackingActor::MainPlayerAttack(AActor* AttackingActor, AActor* AttackedActor)
{
    UE_LOG(LogTemp, Warning, TEXT("MainPlayerAttack called"));
    AMainPaperCharacter* Player = dynamic_cast<AMainPaperCharacter*>(AttackingActor);
    if(Player != nullptr)
    {
        Player->SetAttackAnimation();
    }
}