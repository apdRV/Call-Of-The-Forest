
#pragma once

#include "AttackBase.h"

class AttackedActor : public AttackBase
{
public:
    AttackedActor() : AttackBase(){};

    virtual void TakeDamage(AActor* AttackedActor, AActor* AttackingActor) override;

};