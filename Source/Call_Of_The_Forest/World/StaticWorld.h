
#pragma once

#include "CoreMinimal.h"
#include <map>
#include <memory>
#include <string>
#include <mutex>
#include <vector>
#include <algorithm>
#include "AttackingActor.h"
#include "AttackedActor.h"
#include "../Character/MainCharacterSpriteComponent.h"
#include "GameFramework/Actor.h"
#include "StaticWorld.generated.h"

UCLASS()
class CALL_OF_THE_FOREST_API AStaticWorld : public AActor
{
	GENERATED_BODY()
public:
	AStaticWorld();
	~AStaticWorld();
	void AddActor(std::string Type, AActor* Actor) {
		std::unique_lock lock(m_mutex);
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

	static AStaticWorld* GetStaticWorld() {
		return World;
	}
	
	std::vector<AActor*> GetActor(std::string Type){
		if(Actors.contains(Type)){
			return Actors[Type];
		}
		return std::vector<AActor*>();
	}

	// Function if npc are attacked
	UFUNCTION()
	void MobAttacked(AMob* Mob, float Damage);

	UFUNCTION()
	void AnimalAttacked(AAnimal* Animal, float Damage);

	UFUNCTION()
	void PredatorAttacked(APredator* Predator, float Damage);

	UFUNCTION()
	void TreeAttacked(ATree1* Tree, float Damage);

	//testing attacking from mob to character
	UFUNCTION()
	void MobIsAttacking(AMainPaperCharacter* MainCharacter, AMob* Mob);
	
	// Attacking
	void PlayerAttack(FVector PlayerLocation, EMainCharacterState CharacterState, float Damage);
	//property for overlapping character actors
	UFUNCTION()
	void AddOverlappingActors(AActor* OtherActor);

	UFUNCTION()
	void DeleteOverlappingActors(AActor* OtherActor);
private:
	UPROPERTY()
    TArray<AActor*> OverlappingActors;
	std::map<std::string, std::vector<AActor*>> Actors;
	static AStaticWorld* World;
	std::mutex m_mutex;

	//property for attacking
	AttackingActor ClassToMakeDamage;
	AttackedActor ClassToGetDamage;
};