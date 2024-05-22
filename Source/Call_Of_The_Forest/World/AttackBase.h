
#pragma once

#include "GameFramework/Actor.h"


class AttackBase
{
public:
    AttackBase();

    virtual void TakeDamage(AActor* AttackedActor, AActor* AttackingActor);
    virtual void MakeDamage(AActor* AttackingActor, AActor* AttackedActor);

};