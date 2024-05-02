
#include "StaticWorld.h"
#include "../Resources/Wood/Wood.h"
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
	for (auto &Tree : Actors["Tree"]){
		if(Tree != nullptr){
			if(abs(Tree->GetActorLocation().X - PlayerLocation.X) > 100 || abs(Tree->GetActorLocation().Y - PlayerLocation.Y) > 100){
				continue;
			}
			if(dynamic_cast<ATree1*>(Tree) == nullptr){
				continue;
			}
			if(CharacterState == EMainCharacterState::AttackDown)
			{
				if (Tree->GetActorLocation().X < PlayerLocation.X && PlayerLocation.X - Tree->GetActorLocation().X <= 50 && std::abs(Tree->GetActorLocation().Y - PlayerLocation.Y) <= 20){
					DestroyTree(dynamic_cast<ATree1*>(Tree));
				}
			}
			else if(CharacterState == EMainCharacterState::AttackUp)
			{
				if (Tree->GetActorLocation().X > PlayerLocation.X && Tree->GetActorLocation().X - PlayerLocation.X <= 20 && std::abs(Tree->GetActorLocation().Y - PlayerLocation.Y) <= 20){
					DestroyTree(dynamic_cast<ATree1*>(Tree));
				}
			}
			else if(CharacterState == EMainCharacterState::AttackRight)
			{
				if (Tree->GetActorLocation().Y > PlayerLocation.Y && Tree->GetActorLocation().Y - PlayerLocation.Y <= 27.5 && PlayerLocation.X - Tree->GetActorLocation().X <= 50 && PlayerLocation.X > Tree->GetActorLocation().X){
					DestroyTree(dynamic_cast<ATree1*>(Tree));
				}
			}
			else if(CharacterState == EMainCharacterState::AttackLeft)
			{
				if (Tree->GetActorLocation().Y < PlayerLocation.Y && PlayerLocation.Y - Tree->GetActorLocation().Y <= 27.5 && PlayerLocation.X - Tree->GetActorLocation().X <= 50 && PlayerLocation.X > Tree->GetActorLocation().X){
					DestroyTree(dynamic_cast<ATree1*>(Tree));
				}
			}
		}
		else{
			continue;
		}
	}
}

