
#include "StaticWorld.h"
#include "../Tree1.h"


AStaticWorld::AStaticWorld()
{
}

AStaticWorld::~AStaticWorld()
{
}

void AStaticWorld::PlayerAttack(FVector PlayerLocation, EMainCharacterState CharacterState) {
		for (auto Tree: Actors["Tree"]){
			
				if(CharacterState == EMainCharacterState::AttackDown)
				{
					if (Tree->GetActorLocation().X < PlayerLocation.X && PlayerLocation.X - Tree->GetActorLocation().X <= 100 && std::abs(Tree->GetActorLocation().Y - PlayerLocation.Y) <= 20){
						dynamic_cast<ATree1*>(Tree)->Attacked();
						Tree->Destroy();
					}
				}
				else if(CharacterState == EMainCharacterState::AttackUp)
				{
					if (Tree->GetActorLocation().X > PlayerLocation.X && Tree->GetActorLocation().X - PlayerLocation.X <= 20 && std::abs(Tree->GetActorLocation().Y - PlayerLocation.Y) <= 20){
						dynamic_cast<ATree1*>(Tree)->Attacked();
						Tree->Destroy();
					}
				}
				else if(CharacterState == EMainCharacterState::AttackRight)
				{
					if (Tree->GetActorLocation().Y > PlayerLocation.Y && Tree->GetActorLocation().Y - PlayerLocation.Y <= 27.5 && PlayerLocation.X - Tree->GetActorLocation().X <= 100 && PlayerLocation.X > Tree->GetActorLocation().X){
						dynamic_cast<ATree1*>(Tree)->Attacked();
						Tree->Destroy();
					}
				}
				else if(CharacterState == EMainCharacterState::AttackLeft)
				{
					if (Tree->GetActorLocation().Y < PlayerLocation.Y && PlayerLocation.Y - Tree->GetActorLocation().Y <= 27.5 && PlayerLocation.X - Tree->GetActorLocation().X <= 100 && PlayerLocation.X > Tree->GetActorLocation().X){
						dynamic_cast<ATree1*>(Tree)->Attacked();
						Tree->Destroy();
					}
				}
		}
	}
