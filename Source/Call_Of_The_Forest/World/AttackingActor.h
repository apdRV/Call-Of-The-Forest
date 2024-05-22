
#pragma once

#include "AttackBase.h"

class AttackingActor : public AttackBase
{
public:
    AttackingActor() : AttackBase(){};

    virtual void MakeDamage(AActor* AttackingActor, AActor* AttackedActor) override;
    void MainPlayerAttack(AActor* AttackingActor, AActor* AttackedActor);
};