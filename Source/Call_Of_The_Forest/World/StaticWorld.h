
#pragma once

#include "CoreMinimal.h"
#include <map>
#include <memory>
#include <string>
#include <mutex>
#include <vector>
#include <algorithm>
#include <algorithm>
#include "../Character/MainCharacterSpriteComponent.h"
#include "GameFramework/Actor.h"
#include "StaticWorld.generated.h"

UCLASS()
class CALL_OF_THE_FOREST_API AStaticWorld : public AActor
{
	GENERATED_BODY()
	std::map<std::string, std::vector<AActor*>> Actors;
	static AStaticWorld* World;
public:
	AStaticWorld();
	~AStaticWorld();
	void AddActor(std::string Type, AActor* Actor) {
		if (Actor == nullptr) {
			return;
		}
		if (!Actors.contains(Type)) {
			Actors.insert({Type, std::vector<AActor*>()});
		} else {
			if (std::find(Actors[Type].begin(), Actors[Type].end(), Actor) != Actors[Type].end()) {
				return;
			}
		}
		Actors[Type].push_back(Actor);
	}
	void PlayerAttack(FVector PlayerLocation, EMainCharacterState CharacterState);	
	static AStaticWorld* GetStaticWorld() {
		return World;
	}
};