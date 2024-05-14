
#include "StaticWorld.h"
#include "../Resources/Wood/Wood.h"
#include "../Mobs/Mob.h"
#include "../Animals/Animal.h"
#include "../Animals/Predator.h"
#include "../Tree1.h"

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
void DestroyTree(ATree1* Tree){
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
	UWorld* World = Tree->GetWorld();
	Tree->Destroy();
	World->SpawnActor<AWood>(Location, Rotation, SpawnParams);
}
void AStaticWorld::PlayerAttack(FVector PlayerLocation, EMainCharacterState CharacterState) {
	std::unique_lock lock(m_mutex);
	if (Actors.find("Tree") == Actors.end()){
		return;
	} 
	//auto Trees = Actors["Tree"];
	for (int i = 0; i < Actors["Tree"].size(); i++){
		auto Tree = Actors["Tree"][i];
		if(Tree != nullptr){
			if(abs(Tree->GetActorLocation().X - PlayerLocation.X) > 100 || abs(Tree->GetActorLocation().Y - PlayerLocation.Y) > 100){
				continue;
			}
			if(dynamic_cast<ATree1*>(Tree) == nullptr){
				continue;
			}
			if(CharacterState == EMainCharacterState::AttackDown)
			{
				if (Tree->GetActorLocation().X < PlayerLocation.X && PlayerLocation.X - Tree->GetActorLocation().X <= 100 && std::abs(Tree->GetActorLocation().Y - PlayerLocation.Y) <= 20){
					// OverlappingActors.Remove(Tree);
					DestroyTree(dynamic_cast<ATree1*>(Tree));
					Actors["Tree"].erase(Actors["Tree"].begin() + i);
				}
			}
			else if(CharacterState == EMainCharacterState::AttackUp)
			{
				if (Tree->GetActorLocation().X > PlayerLocation.X && Tree->GetActorLocation().X - PlayerLocation.X <= 20 && std::abs(Tree->GetActorLocation().Y - PlayerLocation.Y) <= 20){
					// OverlappingActors.Remove(Tree);
					DestroyTree(dynamic_cast<ATree1*>(Tree));
					Actors["Tree"].erase(Actors["Tree"].begin() + i);
				}
			}
			else if(CharacterState == EMainCharacterState::AttackRight)
			{
				if (Tree->GetActorLocation().Y > PlayerLocation.Y && Tree->GetActorLocation().Y - PlayerLocation.Y <= 27.5 && PlayerLocation.X - Tree->GetActorLocation().X <= 100 && PlayerLocation.X > Tree->GetActorLocation().X){
					// OverlappingActors.Remove(Tree);
					DestroyTree(dynamic_cast<ATree1*>(Tree));
					Actors["Tree"].erase(Actors["Tree"].begin() + i);
				}
			}
			else if(CharacterState == EMainCharacterState::AttackLeft)
			{
				if (Tree->GetActorLocation().Y < PlayerLocation.Y && PlayerLocation.Y - Tree->GetActorLocation().Y <= 27.5 && PlayerLocation.X - Tree->GetActorLocation().X <= 100 && PlayerLocation.X > Tree->GetActorLocation().X){
					// OverlappingActors.Remove(Tree);
					DestroyTree(dynamic_cast<ATree1*>(Tree));
					Actors["Tree"].erase(Actors["Tree"].begin() + i);
				}
			}
		}
		else{
			continue;
		}
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
	//UWorld* World = Mob->GetWorld();
	for (int i = 0; i < Actors["Mob"].size(); i++){
		if(Mob == Actors["Mob"][i])
		{
			Actors["Mob"].erase(Actors["Mob"].begin() + i);
			break;
		}
	}
	//OverlappingActors.Remove(Mob);
	Mob->Destroy();
	//GetWorld()->SpawnActor<AMeat>(Location, Rotation, SpawnParams);
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
	//UWorld* World = Animal->GetWorld();
	for (int i = 0; i < Actors["Animal"].size(); i++){
		if(Animal == Actors["Animal"][i])
		{
			Actors["Animal"].erase(Actors["Animal"].begin() + i);
			break;
		}
	}
	//OverlappingActors.Remove(Animal);
	Animal->Destroy();
	//GetWorld()->SpawnActor<AMeat>(Location, Rotation, SpawnParams);
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
	//UWorld* World = Predator->GetWorld();
	for (int i = 0; i < Actors["Predator"].size(); i++){
		if(Predator == Actors["Predator"][i])
		{
			Actors["Predator"].erase(Actors["Predator"].begin() + i);
			break;
		}
	}
	//OverlappingActors.Remove(Predator);
	Predator->Destroy();
	//GetWorld()->SpawnActor<AMeat>(Location, Rotation, SpawnParams);
}

void AStaticWorld::PlayerAttacking(FVector PlayerLocation, EMainCharacterState CharacterState)
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
						OverlappingActors.Remove(Tree);
						DestroyTree(Tree);
						//НАДО УДАЛИТЬ ДЕРЕВО ИЗ ОБЩЕЙ МАПЫ
						//Actors["Tree"].erase(Actors["Tree"].begin() + i);
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
						OverlappingActors.Remove(Tree);
						DestroyTree(Tree);
						//НАДО УДАЛИТЬ ДЕРЕВО ИЗ ОБЩЕЙ МАПЫ
						//Actors["Tree"].erase(Actors["Tree"].begin() + i);
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
						OverlappingActors.Remove(Tree);
						DestroyTree(Tree);
						//НАДО УДАЛИТЬ ДЕРЕВО ИЗ ОБЩЕЙ МАПЫ
						//Actors["Tree"].erase(Actors["Tree"].begin() + i);
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
						OverlappingActors.Remove(Tree);
						DestroyTree(Tree);
						//НАДО УДАЛИТЬ ДЕРЕВО ИЗ ОБЩЕЙ МАПЫ
						//Actors["Tree"].erase(Actors["Tree"].begin() + i);
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