
#include "AttackedActor.h"
#include "../Character/MainPaperCharacter.h"
#include "../Mobs/Mob.h"
#include "../Animals/Animal.h"
#include "../Animals/Predator.h"

void AttackedActor::TakeDamage(AActor* AttackedActor, AActor* AttackingActor)
{
    AMob* Mob = dynamic_cast<AMob*>(AttackedActor);
    APredator* Predator = dynamic_cast<APredator*>(AttackedActor);
    AAnimal* Animal = dynamic_cast<AAnimal*>(AttackedActor);
    AMainPaperCharacter* MainCharacter = dynamic_cast<AMainPaperCharacter*>(AttackingActor);
    if(Mob != nullptr && MainCharacter != nullptr)
    {
        Mob->Attacked(MainCharacter->GetDamage());
        MainCharacter->SetAttackAnimation();

    }
    else if(Predator != nullptr && MainCharacter != nullptr)
    {
        Predator->Attacked(MainCharacter->GetDamage());
        MainCharacter->SetAttackAnimation();
    }
    else if(Animal != nullptr && MainCharacter != nullptr)
    {
        Animal->Attacked(MainCharacter->GetDamage());
        MainCharacter->SetAttackAnimation();
    }
}