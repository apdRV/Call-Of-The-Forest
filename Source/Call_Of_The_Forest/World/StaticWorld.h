
#pragma once

#include "CoreMinimal.h"
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include "../Character/MainCharacterSpriteComponent.h"
#include "GameFramework/Actor.h"
#include "StaticWorld.generated.h"

UCLASS()
class CALL_OF_THE_FOREST_API AStaticWorld : public AActor
{
	GENERATED_BODY()

	std::map<std::string, std::vector<AActor*>> Actors;
public:
	AStaticWorld();
	~AStaticWorld();
	void AddActor (std::string Type, AActor* Actor){
		Actors[Type].push_back(Actor);
	}	
	void PlayerAttack(FVector PlayerLocation, EMainCharacterState CharacterState);	
	static AStaticWorld* GetStaticWorld() {
		static AStaticWorld* World = NewObject<AStaticWorld>();
		return World;
	}
};
