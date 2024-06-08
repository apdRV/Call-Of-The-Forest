
#pragma once
#include "../Character/MainPaperCharacter.h"
#include "AttackBase.h"

class AttackingActor : public AttackBase
{
public:
    AttackingActor() : AttackBase(){};

    virtual void MakeDamage(AActor* AttackingActor, AMainPaperCharacter* AttackedActor) override;
    void MainPlayerAttack(AMainPaperCharacter* AttackingActor, AActor* AttackedActor);
};
