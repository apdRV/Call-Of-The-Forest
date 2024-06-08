
#pragma once

#include "../Character/MainPaperCharacter.h"
#include "GameFramework/Actor.h"


class AttackBase
{
public:
    AttackBase();

    virtual void TakeDamage(AMainPaperCharacter* AttackedActor, AActor* AttackingActor);
    virtual void MakeDamage(AActor* AttackingActor, AMainPaperCharacter* AttackedActor);

};
