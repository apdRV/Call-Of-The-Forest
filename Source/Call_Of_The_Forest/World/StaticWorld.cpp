
#include "StaticWorld.h"
#include "../Resources/Wood/Wood.h"
#include "../Mobs/Mob.h"
#include "../Animals/Animal.h"
#include "../Animals/Predator.h"
#include "../Spawners/Tree1.h"
#include "ResourcesSpawner.h"

AStaticWorld* AStaticWorld::World = nullptr;
AStaticWorld::AStaticWorld()
{
	if (World == nullptr){
		World = this;
	}
}

AStaticWorld::~AStaticWorld()
{
	World = nullptr;
}
void AStaticWorld::TreeDestroy(ATree1* Tree)
{
	FVector Location = Tree->GetActorLocation();
	Location.X += 10;
	Location.Z -= 0.4;
	FRotator Rotation = {0, 0, 0};
	FActorSpawnParameters SpawnParams;
	SpawnParams.bNoFail = true;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	auto iter = std::find(Actors["Tree"].begin(), Actors["Tree"].end(), Tree);
	if(iter != Actors["Tree"].end())
	{
		Actors["Tree"].erase(iter);
		UE_LOG(LogTemp, Warning, TEXT("Tree deleted"));
	}

	Tree->Destroy();
	AResourcesSpawner* ResourceSpawner = dynamic_cast<AResourcesSpawner*>(Actors["ResourcesSpawner"][0]);
	if(ResourceSpawner != nullptr)
	{
		ResourceSpawner->SpawnResource(Location, Rotation, SpawnParams, EResourceType::Wood);
	}
}

void AStaticWorld::MobDestroy(AMob* Mob)
{
	float DelayBeforeDestroy = 1.5f;
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, [Mob, this]()
	{
		FVector Location = Mob->GetActorLocation();
		Location.X += 10;
		Location.Z -= 0.4;
		FRotator Rotation = {0, 0, 0};
		FActorSpawnParameters SpawnParams;
		SpawnParams.bNoFail = true;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		auto iter = std::find(Actors["Mob"].begin(), Actors["Mob"].end(), Mob);
		if(iter != Actors["Mob"].end())
		{
			Actors["Mob"].erase(iter);
			UE_LOG(LogTemp, Warning, TEXT("Mob deleted"));
		}
		Mob->Destroy();
		AResourcesSpawner* ResourceSpawner = dynamic_cast<AResourcesSpawner*>(Actors["ResourcesSpawner"][0]);
		if(ResourceSpawner != nullptr)
		{
			ResourceSpawner->SpawnResource(Location, Rotation, SpawnParams, EResourceType::Trophy);
		}
	}, DelayBeforeDestroy, false); 
}

void AStaticWorld::AnimalDestroy(AAnimal* Animal)
{
	float DelayBeforeDestroy = 1.5f;
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, [Animal, this]()
	{
		FVector Location = Animal->GetActorLocation();
		Location.X += 10;
		Location.Z -= 0.4;
		FRotator Rotation = {0, 0, 0};
		FActorSpawnParameters SpawnParams;
		SpawnParams.bNoFail = true;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		auto iter = std::find(Actors["Animal"].begin(), Actors["Animal"].end(), Animal);
		if(iter != Actors["Animal"].end())
		{
			Actors["Animal"].erase(iter);
			UE_LOG(LogTemp, Warning, TEXT("Animal deleted"));
		}

		Animal->Destroy();
		AResourcesSpawner* ResourceSpawner = dynamic_cast<AResourcesSpawner*>(Actors["ResourcesSpawner"][0]);
		if(ResourceSpawner != nullptr)
		{
			ResourceSpawner->SpawnResource(Location, Rotation, SpawnParams, EResourceType::Meat);
		}
	}, DelayBeforeDestroy, false); 
}

void AStaticWorld::PredatorDestroy(APredator* Predator)
{
	float DelayBeforeDestroy = 1.5f;
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, [Predator, this]()
	{
		FVector Location = Predator->GetActorLocation();
		Location.X += 10;
		Location.Z -= 0.4;
		FRotator Rotation = {0, 0, 0};
		FActorSpawnParameters SpawnParams;
		SpawnParams.bNoFail = true;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		auto iter = std::find(Actors["Predator"].begin(), Actors["Predator"].end(), Predator);
		if(iter != Actors["Predator"].end())
		{
			Actors["Predator"].erase(iter);
			UE_LOG(LogTemp, Warning, TEXT("Predator deleted"));
		}

		Predator->Destroy();
		AResourcesSpawner* ResourceSpawner = dynamic_cast<AResourcesSpawner*>(Actors["ResourcesSpawner"][0]);
		if(ResourceSpawner != nullptr)
		{
			ResourceSpawner->SpawnResource(Location, Rotation, SpawnParams, EResourceType::Meat);
		}
	}, DelayBeforeDestroy, false); 
}

void AStaticWorld::PlayerAttack(FVector PlayerLocation, EMainCharacterState CharacterState, AMainPaperCharacter* Player)
{
	std::unique_lock lock(m_mutex);
	for(int32 i = 0; i < OverlappingActors.Num(); i++)
	{
		auto Actor = OverlappingActors[i];
		ClassToMakeDamage.MainPlayerAttack(Player, Actor);
		ClassToGetDamage.TakeDamageNpc(Actor, Player);
		AMob* Mob = dynamic_cast<AMob*>(Actor);
		AAnimal* Animal = dynamic_cast<AAnimal*>(Actor);
		APredator* Predator = dynamic_cast<APredator*>(Actor);
		ATree1* Tree = dynamic_cast<ATree1*>(Actor);
		if(Mob != nullptr && Mob->GetbIsDead())
		{
			MobDestroy(Mob);
		}
		else if(Animal != nullptr && Animal->GetbIsDead())
		{
			AnimalDestroy(Animal);
		}
		else if(Predator != nullptr && Predator->GetbIsDead())
		{
			PredatorDestroy(Predator);
		}
		else if(Tree != nullptr && Tree->GetbIsDead())
		{
			TreeDestroy(Tree);
		}
	}

}

void AStaticWorld::AddOverlappingActors(AActor* OtherActor)
{
    AMob* Mob = dynamic_cast<AMob*>(OtherActor);
    if (Mob != nullptr)
    {
        Mob->SetbIsTriggered(true);
        OverlappingActors.Add(OtherActor);
    }
    AAnimal* Animal = dynamic_cast<AAnimal*>(OtherActor);
    if(Animal != nullptr){
        Animal->SetbIsActive(true);
        OverlappingActors.Add(OtherActor);
    }
    APredator* Predator = dynamic_cast<APredator*>(OtherActor);
    if(Predator != nullptr){
        Predator->SetbIsActive(true);
        OverlappingActors.Add(OtherActor);
    }
	ATree1* Tree = dynamic_cast<ATree1*>(OtherActor);
	if(Tree != nullptr){
		OverlappingActors.Add(OtherActor);
	}
}

void AStaticWorld::DeleteOverlappingActors(AActor* OtherActor)
{
    AMob* Mob = dynamic_cast<AMob*>(OtherActor);
    if(Mob != nullptr){
        Mob->SetbIsTriggered(false);
		OverlappingActors.Remove(OtherActor);
    }
    AAnimal* Animal = dynamic_cast<AAnimal*>(OtherActor);
    if(Animal != nullptr){
        Animal->SetbIsActive(false);
		OverlappingActors.Remove(OtherActor);
    }
    APredator* Predator = dynamic_cast<APredator*>(OtherActor);
    if(Predator != nullptr){
        Predator->SetbIsActive(false);
		OverlappingActors.Remove(OtherActor);
    }
	ATree1* Tree = dynamic_cast<ATree1*>(OtherActor);
	if(Tree != nullptr){
		OverlappingActors.Remove(OtherActor);
	}
}

void AStaticWorld::MobIsAttacking(AMainPaperCharacter* MainCharacter, AMob* Mob)
{
	if(FVector::Dist(MainCharacter->GetActorLocation(), Mob->GetActorLocation()) <= 100.0f)
	{
		ClassToMakeDamage.MakeDamage(Mob, MainCharacter);
		ClassToGetDamage.TakeDamage(MainCharacter, Mob);
	}
}

void AStaticWorld::PredatorIsAttacking(AMainPaperCharacter* MainCharacter, APredator* Predator)
{
	if(FVector::Dist(MainCharacter->GetActorLocation(), Predator->GetActorLocation()) <= 100.0f)
	{
		ClassToMakeDamage.MakeDamage(Predator, MainCharacter);
		ClassToGetDamage.TakeDamage(MainCharacter, Predator);
	}
}