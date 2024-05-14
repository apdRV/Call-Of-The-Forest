
#include "StaticWorld.h"
#include "../Resources/Wood/Wood.h"
#include "../Mobs/Mob.h"
#include "../Animals/Animal.h"
#include "../Animals/Predator.h"
#include "../Tree1.h"
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
void AStaticWorld::TreeAttacked(ATree1* Tree, float Damage){
	if(Tree == nullptr){
		return;
	}
	//Tree->Attacked();
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

void AStaticWorld::MobAttacked(AMob* Mob, float Damage)
{
	if(Mob == nullptr){
		return;
	}
	Mob->Attacked(Damage); //?
	if(Mob->GetbIsDead())
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
	}
}

void AStaticWorld::AnimalAttacked(AAnimal* Animal, float Damage)
{
	if(Animal == nullptr){
		return;
	}
	Animal->Attacked(Damage); //?
	if(Animal->GetbIsDead())
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
	}
}

void AStaticWorld::PredatorAttacked(APredator* Predator, float Damage)
{
	if(Predator == nullptr){
		return;
	}
	Predator->Attacked(Damage); //?
	if(Predator->GetbIsDead())
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
	}
}

void AStaticWorld::PlayerAttack(FVector PlayerLocation, EMainCharacterState CharacterState, float Damage)
{
	std::unique_lock lock(m_mutex);
	for(int32 i = 0; i < OverlappingActors.Num(); i++)
	{
		auto Actor = OverlappingActors[i];
		if(Actor != nullptr)
		{
			if(abs(Actor->GetActorLocation().X - PlayerLocation.X) > 100 || abs(Actor->GetActorLocation().Y - PlayerLocation.Y) > 100)
			{
				continue;
			}
			AMob* Mob = dynamic_cast<AMob*>(Actor);
			AAnimal* Animal = dynamic_cast<AAnimal*>(Actor);
			APredator* Predator = dynamic_cast<APredator*>(Actor);
			ATree1* Tree = dynamic_cast<ATree1*>(Actor);

			if(CharacterState == EMainCharacterState::AttackDown)
			{

				if (Actor->GetActorLocation().X < PlayerLocation.X && abs(PlayerLocation.X - Actor->GetActorLocation().X) <= 30 && std::abs(Actor->GetActorLocation().Y - PlayerLocation.Y) <= 15)
				{
					if(Mob != nullptr)
					{
						MobAttacked(Mob, Damage);
					}
					else if(Animal != nullptr)
					{
						AnimalAttacked(Animal, Damage);
					}
					else if(Predator != nullptr)
					{
						PredatorAttacked(Predator, Damage);
					}
					else if(Tree != nullptr)
					{
						TreeAttacked(Tree, Damage);
					}
				}
			}
			else if(CharacterState == EMainCharacterState::AttackUp)
			{
				if (Actor->GetActorLocation().X > PlayerLocation.X && Actor->GetActorLocation().X - PlayerLocation.X <= 20 && std::abs(Actor->GetActorLocation().Y - PlayerLocation.Y) <= 20){
					if(Mob != nullptr)
					{
						MobAttacked(Mob, Damage);
					}
					else if(Animal != nullptr)
					{
						AnimalAttacked(Animal, Damage);
					}
					else if(Predator != nullptr)
					{
						PredatorAttacked(Predator, Damage);
					}
					else if(Tree != nullptr)
					{
						TreeAttacked(Tree, Damage);
					}
				}
			}
			else if(CharacterState == EMainCharacterState::AttackRight)
			{
				if (Actor->GetActorLocation().Y > PlayerLocation.Y && Actor->GetActorLocation().Y - PlayerLocation.Y <= 27.5 && PlayerLocation.X - Actor->GetActorLocation().X <= 27.5 && PlayerLocation.X > Actor->GetActorLocation().X){
					if(Mob != nullptr)
					{
						MobAttacked(Mob, Damage);
					}
					else if(Animal != nullptr)
					{
						AnimalAttacked(Animal, Damage);
					}
					else if(Predator != nullptr)
					{
						PredatorAttacked(Predator, Damage);
					}
					else if(Tree != nullptr)
					{
						TreeAttacked(Tree, Damage);
					}
				}
			}
			else if(CharacterState == EMainCharacterState::AttackLeft)
			{
				if (Actor->GetActorLocation().Y < PlayerLocation.Y && PlayerLocation.Y - Actor->GetActorLocation().Y <= 27.5 && PlayerLocation.X - Actor->GetActorLocation().X <= 100 && PlayerLocation.X > Actor->GetActorLocation().X){
					if(Mob != nullptr)
					{
						MobAttacked(Mob, Damage);
					}
					else if(Animal != nullptr)
					{
						AnimalAttacked(Animal, Damage);
					}
					else if(Predator != nullptr)
					{
						PredatorAttacked(Predator, Damage);
					}
					else if(Tree != nullptr)
					{
						TreeAttacked(Tree, Damage);
					}
				}
			}
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