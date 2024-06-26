
#include "StaticWorld.h"
#include "../Resources/Wood/Wood.h"
#include "../Mobs/Mob.h"
#include "../Animals/Animal.h"
#include "../Animals/Predator.h"
#include "../Enviroment/EnviromentObject.h"
#include "ResourcesSpawner.h"

AStaticWorld* AStaticWorld::World = nullptr;
AStaticWorld::AStaticWorld()
{
	if (World == nullptr){
		World = this;
	}
	bReplicates = true;
}

AStaticWorld::~AStaticWorld()
{
	World = nullptr;
}

void AStaticWorld::EnviromentObjectDestroy(AEnviromentObject* EnviromentObject)
{
	FVector Location = EnviromentObject->GetActorLocation();
	Location.X += 10;
	Location.Z -= 0.4;
	FRotator Rotation = {0, 0, 0};
	FActorSpawnParameters SpawnParams;
	SpawnParams.bNoFail = true;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	auto iter = std::find(Actors["EnviromentObject"].begin(), Actors["EnviromentObject"].end(), EnviromentObject);
	if(iter == Actors["EnviromentObject"].end()) return;
	Actors["EnviromentObject"].erase(iter);
	UE_LOG(LogTemp, Warning, TEXT("EnviromentObject deleted"));
	AResourcesSpawner* ResourceSpawner = dynamic_cast<AResourcesSpawner*>(Actors["ResourcesSpawner"][0]);
	EEnviromentObjectType Object;
	if(ResourceSpawner != nullptr)
	{
		Object = ResourceSpawner->DetermineObjectType(EnviromentObject);
	}
	EnviromentObject->Destroy();
	if(ResourceSpawner != nullptr)
	{
		ResourceSpawner->SpawnEnviromentResource(Location, Rotation, SpawnParams, Object);
	}
}

void AStaticWorld::MobDestroy(AMob* Mob)
{
	Mob->SetbIsDestroyed(true);
	float DelayBeforeDestroy = 1.5f;
	FTimerHandle TimerHandle;
	Mob->GetWorldTimerManager().SetTimer(TimerHandle, [Mob, this]()
	{
		FVector Location = Mob->GetActorLocation();
		Location.X += 10;
		Location.Z -= 0.4;
		FRotator Rotation = {0, 0, 0};
		FActorSpawnParameters SpawnParams;
		SpawnParams.bNoFail = true;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		UE_LOG(LogTemp, Warning, TEXT("Mob deleted"));
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
	Animal->SetbIsDestroyed(true);
	float DelayBeforeDestroy = 1.5f;
	FTimerHandle TimerHandle;
	Animal->GetWorldTimerManager().SetTimer(TimerHandle, [Animal, this]()
	{
		FVector Location = Animal->GetActorLocation();
		Location.X += 10;
		Location.Z -= 0.4;
		FRotator Rotation = {0, 0, 0};
		FActorSpawnParameters SpawnParams;
		SpawnParams.bNoFail = true;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		UE_LOG(LogTemp, Warning, TEXT("Animal deleted"));
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
	Predator->SetbIsDestroyed(true);
	float DelayBeforeDestroy = 1.5f;
	FTimerHandle TimerHandle;
	Predator->GetWorldTimerManager().SetTimer(TimerHandle, [Predator, this]()
	{
		FVector Location = Predator->GetActorLocation();
		Location.X += 10;
		Location.Z -= 0.4;
		FRotator Rotation = {0, 0, 0};
		FActorSpawnParameters SpawnParams;
		SpawnParams.bNoFail = true;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		UE_LOG(LogTemp, Warning, TEXT("Predator deleted"));
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
	UE_LOG(LogTemp, Warning, TEXT("Player attack called"));
	std::unique_lock lock(m_mutex);
	for(int32 i = 0; i < OverlappingActors.Num(); i++)
	{
		auto Actor = OverlappingActors[i];
		ClassToMakeDamage.MainPlayerAttack(Player, Actor);
		ClassToGetDamage.TakeDamageNpc(Actor, Player);
		AMob* Mob = dynamic_cast<AMob*>(Actor);
		AAnimal* Animal = dynamic_cast<AAnimal*>(Actor);
		APredator* Predator = dynamic_cast<APredator*>(Actor);
		AEnviromentObject* EnviromentObject = dynamic_cast<AEnviromentObject*>(Actor);
		if(Mob != nullptr && Mob->GetbIsDead() && !Mob->GetbIsDestroyed())
		{
			MobDestroy(Mob);
		}
		else if(Animal != nullptr && Animal->GetbIsDead() && !Animal->GetbIsDestroyed())
		{
			AnimalDestroy(Animal);
		}
		else if(Predator != nullptr && Predator->GetbIsDead() && !Predator->GetbIsDestroyed())
		{
			PredatorDestroy(Predator);
		}
		else if(EnviromentObject != nullptr && EnviromentObject->GetbIsDead())
		{
			EnviromentObjectDestroy(EnviromentObject);
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
	AEnviromentObject* EnviromentObject = dynamic_cast<AEnviromentObject*>(OtherActor);
	if(EnviromentObject != nullptr)
	{
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
	AEnviromentObject* EnviromentObject = dynamic_cast<AEnviromentObject*>(OtherActor);
	if(EnviromentObject != nullptr)
	{
		OverlappingActors.Remove(OtherActor);
	}
}

void AStaticWorld::MobIsAttacking(AMainPaperCharacter* MainCharacter, AMob* Mob)
{
	if (Mob->GetbIsDead()) return;
	if(FVector::Dist(MainCharacter->GetActorLocation(), Mob->GetActorLocation()) <= 100.0f)
	{
		ClassToMakeDamage.MakeDamage(Mob, MainCharacter);
		ClassToGetDamage.TakeDamage(MainCharacter, Mob);
	}
}

void AStaticWorld::PredatorIsAttacking(AMainPaperCharacter* MainCharacter, APredator* Predator)
{
	if (Predator->GetbIsDead()) return;
	if(FVector::Dist(MainCharacter->GetActorLocation(), Predator->GetActorLocation()) <= 100.0f)
	{
		ClassToMakeDamage.MakeDamage(Predator, MainCharacter);
		ClassToGetDamage.TakeDamage(MainCharacter, Predator);
	}
}
