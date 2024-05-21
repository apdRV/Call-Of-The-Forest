
#include "AttackingActor.h"
#include "../Character/MainPaperCharacter.h"
#include "../Mobs/Mob.h"
#include "../Animals/Animal.h"
#include "Math/UnrealMathUtility.h"
#include "../Animals/Predator.h"
#include "../Tree1.h"

void AttackingActor::MakeDamage(AActor* AttackingActor, AActor* AttackedActor)
{
    UE_LOG(LogTemp, Warning, TEXT("AttackingActor::MakeDamage"));
    AMob* MobAttacking = dynamic_cast<AMob*>(AttackingActor);
    APredator* PredatorAttacking = dynamic_cast<APredator*>(AttackingActor);
    AMainPaperCharacter* MainCharacterAttacked = dynamic_cast<AMainPaperCharacter*>(AttackedActor);
    if(MainCharacterAttacked != nullptr && MobAttacking != nullptr)
    {
        if((MobAttacking->GetMobState() == EMobState::IdleLeftDown || MobAttacking->GetMobState() == EMobState::LeftDown) && MainCharacterAttacked->GetActorLocation().Y <= MobAttacking->GetActorLocation().Y && 
        (MobAttacking->GetActorLocation().Y - MainCharacterAttacked->GetActorLocation().Y) <= 30.0f && FMath::Abs(MobAttacking->GetActorLocation().X - MainCharacterAttacked->GetActorLocation().X) <= 30.0f)
        {
            MobAttacking->SetMobState(EMobState::AttackLeftDown);
            MainCharacterAttacked->Attacked(MobAttacking->GetBaseDamage());
        }
        else if((MobAttacking->GetMobState() == EMobState::IdleRightUp || MobAttacking->GetMobState() == EMobState::RightUp) && MainCharacterAttacked->GetActorLocation().Y >= MobAttacking->GetActorLocation().Y && 
        (MainCharacterAttacked->GetActorLocation().Y - MobAttacking->GetActorLocation().Y) <= 30.0f && FMath::Abs(MobAttacking->GetActorLocation().X - MainCharacterAttacked->GetActorLocation().X) <= 30.0f)
        {
            MobAttacking->SetMobState(EMobState::AttackRightUp);
            MainCharacterAttacked->Attacked(MobAttacking->GetBaseDamage());
        }
    }
    else if(MainCharacterAttacked != nullptr && PredatorAttacking != nullptr)
    {
        if((PredatorAttacking->GetPredatorState() == EPredatorState::IdleLeftDown || PredatorAttacking->GetPredatorState() == EPredatorState::LeftDown) && MainCharacterAttacked->GetActorLocation().Y <= PredatorAttacking->GetActorLocation().Y && 
        (PredatorAttacking->GetActorLocation().Y - MainCharacterAttacked->GetActorLocation().Y) <= 30.0f && FMath::Abs(PredatorAttacking->GetActorLocation().X - MainCharacterAttacked->GetActorLocation().X) <= 30.0f)
        {
            PredatorAttacking->SetPredatorState(EPredatorState::AttackingLeftDown);
            MainCharacterAttacked->Attacked(PredatorAttacking->GetDamage());
        }
        else if((PredatorAttacking->GetPredatorState() == EPredatorState::IdleRightUp || PredatorAttacking->GetPredatorState() == EPredatorState::RightUp) && MainCharacterAttacked->GetActorLocation().Y >= PredatorAttacking->GetActorLocation().Y && 
        (MainCharacterAttacked->GetActorLocation().Y - PredatorAttacking->GetActorLocation().Y) <= 30.0f && FMath::Abs(PredatorAttacking->GetActorLocation().X - MainCharacterAttacked->GetActorLocation().X) <= 30.0f)
        {
            PredatorAttacking->SetPredatorState(EPredatorState::AttackingRightUp);
            MainCharacterAttacked->Attacked(PredatorAttacking->GetDamage());
        }
    }
}

void AttackingActor::MainPlayerAttack(AActor* AttackingActor, AActor* AttackedActor)
{
    if(AttackingActor == nullptr || AttackedActor == nullptr)
    {
        return;
    }
    if(FVector::Dist(AttackingActor->GetActorLocation(), AttackedActor->GetActorLocation()) > 100.0f)
    {
        return;
    }

    AMainPaperCharacter* Player = dynamic_cast<AMainPaperCharacter*>(AttackingActor);
    if(Player == nullptr)
    {
        return;
    }

    AMob* Mob = dynamic_cast<AMob*>(AttackedActor);
    AAnimal* Animal = dynamic_cast<AAnimal*>(AttackedActor);
    APredator* Predator = dynamic_cast<APredator*>(AttackedActor);
    ATree1* Tree = dynamic_cast<ATree1*>(AttackedActor);
    FVector PlayerLocation = Player->GetActorLocation();
    switch(Player->GetCharacterState())
    {
        case EMainCharacterState::AttackDown:
            if (AttackedActor->GetActorLocation().X < PlayerLocation.X && std::abs(PlayerLocation.X - AttackedActor->GetActorLocation().X) <= 30 && std::abs(AttackedActor->GetActorLocation().Y - PlayerLocation.Y) <= 30)
            {
                if(Mob != nullptr)
                {
                    Mob->Attacked(Player->GetDamage());
                    return;
                }
                else if(Animal != nullptr)
                {
                    Animal->Attacked(Player->GetDamage());
                    return;
                }
                else if(Predator != nullptr)
                {
                    Predator->Attacked(Player->GetDamage());
                    return;
                }
                else if(Tree != nullptr)
                {
                    Tree->Attacked(Player->GetDamage());
                    return;
                }
            }
            break;
        case EMainCharacterState::AttackUp:
            if (AttackedActor->GetActorLocation().X > PlayerLocation.X && AttackedActor->GetActorLocation().X - PlayerLocation.X <= 30 && std::abs(AttackedActor->GetActorLocation().Y - PlayerLocation.Y) <= 30){
                if(Mob != nullptr)
                {
                    Mob->Attacked(Player->GetDamage());
                    return;
                }
                else if(Animal != nullptr)
                {
                    Animal->Attacked(Player->GetDamage());
                    return;
                }
                else if(Predator != nullptr)
                {
                    Predator->Attacked(Player->GetDamage());
                    return;
                }
                else if(Tree != nullptr)
                {
                    Tree->Attacked(Player->GetDamage());
                    return;
                }
            }
            break;
        case EMainCharacterState::AttackRight:
            if (AttackedActor->GetActorLocation().Y > PlayerLocation.Y && AttackedActor->GetActorLocation().Y - PlayerLocation.Y <= 30 && std::abs(PlayerLocation.X - AttackedActor->GetActorLocation().X) <= 30 /*&& PlayerLocation.X > AttackedActor->GetActorLocation().X*/){
                if(Mob != nullptr)
                {
                    Mob->Attacked(Player->GetDamage());
                    return;
                }
                else if(Animal != nullptr)
                {
                    Animal->Attacked(Player->GetDamage());
                    return;
                }
                else if(Predator != nullptr)
                {
                    Predator->Attacked(Player->GetDamage());
                    return;
                }
                else if(Tree != nullptr)
                {
                    Tree->Attacked(Player->GetDamage());
                    return;
                }
            }
            break;
        case EMainCharacterState::AttackLeft:
            if (AttackedActor->GetActorLocation().Y < PlayerLocation.Y && PlayerLocation.Y - AttackedActor->GetActorLocation().Y <= 30 && std::abs(PlayerLocation.X - AttackedActor->GetActorLocation().X) <= 30 /*&& PlayerLocation.X > AttackedActor->GetActorLocation().X*/){
                if(Mob != nullptr)
                {
                    Mob->Attacked(Player->GetDamage());
                    return;
                }
                else if(Animal != nullptr)
                {
                    Animal->Attacked(Player->GetDamage());
                    return;
                }
                else if(Predator != nullptr)
                {
                    Predator->Attacked(Player->GetDamage());
                    return;
                }
                else if(Tree != nullptr)
                {
                    Tree->Attacked(Player->GetDamage());
                    return;
                }
            }
            break;
    }
}