
#pragma once

#include "../Character/MainPaperCharacter.h"
#include "AttackBase.h"

class AttackedActor : public AttackBase
{
public:
    AttackedActor() : AttackBase(){};

    virtual void TakeDamage(AMainPaperCharacter* AttackedActor, AActor* AttackingActor) override;
    void TakeDamageNpc(AActor* AttackedActor, AMainPaperCharacter* AttackingActor);
};
