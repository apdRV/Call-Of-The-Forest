
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
void AStaticWorld::TreeAttacked(ATree1* Tree){
	if(Tree == nullptr){
		return;
	}
	Tree->Attacked();
	FVector Location = Tree->GetActorLocation();
	Location.X += 10;
	Location.Z -= 0.4;
	FRotator Rotation = {0, 0, 0};
	FActorSpawnParameters SpawnParams;
	SpawnParams.bNoFail = true;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	for (int i = 0; i < Actors["Tree"].size(); i++){
		if(Tree == Actors["Tree"][i])
		{
			Actors["Tree"].erase(Actors["Tree"].begin() + i);
			UE_LOG(LogTemp, Warning, TEXT("Tree deleted"));
			break;
		}
	}
	Tree->Destroy();
	AResourcesSpawner* ResourceSpawner = dynamic_cast<AResourcesSpawner*>(Actors["ResourcesSpawner"][0]);
	if(ResourceSpawner != nullptr)
	{
		ResourceSpawner->SpawnResource(Location, Rotation, SpawnParams, EResourceType::Wood);
	}
}

void AStaticWorld::MobAttacked(AMob* Mob)
{
	if(Mob == nullptr){
		return;
	}
	//Mob->Attacked(); //?
	FVector Location = Mob->GetActorLocation();
	Location.X += 10;
	Location.Z -= 0.4;
	FRotator Rotation = {0, 0, 0};
	FActorSpawnParameters SpawnParams;
	SpawnParams.bNoFail = true;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	for (int i = 0; i < Actors["Mob"].size(); i++){
		if(Mob == Actors["Mob"][i])
		{
			Actors["Mob"].erase(Actors["Mob"].begin() + i);
			UE_LOG(LogTemp, Warning, TEXT("Mob deleted"));
			break;
		}
	}
	Mob->Destroy();
	AResourcesSpawner* ResourceSpawner = dynamic_cast<AResourcesSpawner*>(Actors["ResourcesSpawner"][0]);
	if(ResourceSpawner != nullptr)
	{
		ResourceSpawner->SpawnResource(Location, Rotation, SpawnParams, EResourceType::Trophy);
	}
}

void AStaticWorld::AnimalAttacked(AAnimal* Animal)
{
	if(Animal == nullptr){
		return;
	}
	//Animal->Attacked(); //?
	FVector Location = Animal->GetActorLocation();
	Location.X += 10;
	Location.Z -= 0.4;
	FRotator Rotation = {0, 0, 0};
	FActorSpawnParameters SpawnParams;
	SpawnParams.bNoFail = true;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	for (int i = 0; i < Actors["Animal"].size(); i++){
		if(Animal == Actors["Animal"][i])
		{
			Actors["Animal"].erase(Actors["Animal"].begin() + i);
			UE_LOG(LogTemp, Warning, TEXT("Animal deleted"));
			break;
		}
	}
	AResourcesSpawner* ResourceSpawner = dynamic_cast<AResourcesSpawner*>(Actors["ResourcesSpawner"][0]);
	if(ResourceSpawner != nullptr)
	{
		ResourceSpawner->SpawnResource(Location, Rotation, SpawnParams, EResourceType::Meat);
	}
	Animal->Destroy();
}

void AStaticWorld::PredatorAttacked(APredator* Predator)
{
	if(Predator == nullptr){
		return;
	}
	//Predator->Attacked(); //?
	FVector Location = Predator->GetActorLocation();
	Location.X += 10;
	Location.Z -= 0.4;
	FRotator Rotation = {0, 0, 0};
	FActorSpawnParameters SpawnParams;
	SpawnParams.bNoFail = true;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	for (int i = 0; i < Actors["Predator"].size(); i++){
		if(Predator == Actors["Predator"][i])
		{
			Actors["Predator"].erase(Actors["Predator"].begin() + i);
			UE_LOG(LogTemp, Warning, TEXT("Predator deleted"));
			break;
		}
	}
	AResourcesSpawner* ResourceSpawner = dynamic_cast<AResourcesSpawner*>(Actors["ResourcesSpawner"][0]);
	if(ResourceSpawner != nullptr)
	{
		ResourceSpawner->SpawnResource(Location, Rotation, SpawnParams, EResourceType::Meat);
	}
	Predator->Destroy();
}

void AStaticWorld::PlayerAttack(FVector PlayerLocation, EMainCharacterState CharacterState)
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

				if (Actor->GetActorLocation().X < PlayerLocation.X && PlayerLocation.X - Actor->GetActorLocation().X <= 100 && std::abs(Actor->GetActorLocation().Y - PlayerLocation.Y) <= 20)
				{
					if(Mob != nullptr)
					{
						MobAttacked(Mob);
					}
					else if(Animal != nullptr)
					{
						AnimalAttacked(Animal);
					}
					else if(Predator != nullptr)
					{
						PredatorAttacked(Predator);
					}
					else if(Tree != nullptr)
					{
						TreeAttacked(Tree);
					}
				}
			}
			else if(CharacterState == EMainCharacterState::AttackUp)
			{
				if (Actor->GetActorLocation().X > PlayerLocation.X && Actor->GetActorLocation().X - PlayerLocation.X <= 20 && std::abs(Actor->GetActorLocation().Y - PlayerLocation.Y) <= 20){
					if(Mob != nullptr)
					{
						MobAttacked(Mob);
					}
					else if(Animal != nullptr)
					{
						AnimalAttacked(Animal);
					}
					else if(Predator != nullptr)
					{
						PredatorAttacked(Predator);
					}
					else if(Tree != nullptr)
					{
						TreeAttacked(Tree);
					}
				}
			}
			else if(CharacterState == EMainCharacterState::AttackRight)
			{
				if (Actor->GetActorLocation().Y > PlayerLocation.Y && Actor->GetActorLocation().Y - PlayerLocation.Y <= 27.5 && PlayerLocation.X - Actor->GetActorLocation().X <= 100 && PlayerLocation.X > Actor->GetActorLocation().X){
					if(Mob != nullptr)
					{
						MobAttacked(Mob);
					}
					else if(Animal != nullptr)
					{
						AnimalAttacked(Animal);
					}
					else if(Predator != nullptr)
					{
						PredatorAttacked(Predator);
					}
					else if(Tree != nullptr)
					{
						TreeAttacked(Tree);
					}
				}
			}
			else if(CharacterState == EMainCharacterState::AttackLeft)
			{
				if (Actor->GetActorLocation().Y < PlayerLocation.Y && PlayerLocation.Y - Actor->GetActorLocation().Y <= 27.5 && PlayerLocation.X - Actor->GetActorLocation().X <= 100 && PlayerLocation.X > Actor->GetActorLocation().X){
					if(Mob != nullptr)
					{
						MobAttacked(Mob);
					}
					else if(Animal != nullptr)
					{
						AnimalAttacked(Animal);
					}
					else if(Predator != nullptr)
					{
						PredatorAttacked(Predator);
					}
					else if(Tree != nullptr)
					{
						TreeAttacked(Tree);
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
        Mob->SetTriggered(true);
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
        Mob->SetTriggered(false);
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