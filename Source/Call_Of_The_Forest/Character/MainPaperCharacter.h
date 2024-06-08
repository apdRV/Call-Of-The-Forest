
#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "../World/StaticWorld.h"
#include "../Animals/Animal.h"
#include "../Animals/Predator.h"
#include "MainCharacterSpriteComponent.h"
#include "../World/AttackedDerivedDeclaration.h"
#include "Engine/EngineTypes.h"
#include "Net/UnrealNetwork.h"
#include "MainPaperCharacter.generated.h"
/**
 * 
 */

UCLASS()
class CALL_OF_THE_FOREST_API AMainPaperCharacter : public APaperCharacter
{
	GENERATED_BODY()

public:
	AMainPaperCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	float GetDamage();

	UFUNCTION()
	EMainCharacterState GetCharacterState();

	UFUNCTION(BlueprintCallable)
	bool GetbIsDead();

protected:
    UPROPERTY()
	AStaticWorld* World;

	UPROPERTY() 
	float Health;
	
	UPROPERTY(Replicated)
	bool bIsMoving;

	UPROPERTY(Replicated)
	bool bIsDead;

	UPROPERTY(ReplicatedUsing = OnRep_Attacking)
	bool bIsAttacking;

	UFUNCTION()
	void OnRep_Attacking();

	UPROPERTY()
	FTimerHandle AttackTimerHandle;

	UPROPERTY(Replicated)
	float Damage;

	UPROPERTY(Replicated)
	EMainCharacterState CharacterState;

	UPROPERTY(Replicated)
	EMainCharacterState LastMoveDirection;

	UFUNCTION()
	virtual void BeginPlay() override;

	UFUNCTION()
	void Die(); 

	UFUNCTION()
	void PickUpItem(float Value); 

	UFUNCTION()
    void MoveForwardBackward(float Value);

	UFUNCTION(Server, Reliable)
	void ServerMoveForwardBackward(float Value);

	UFUNCTION()
    void MoveRightLeft(float Value);

	UFUNCTION(Server, Reliable)
	void ServerMoveRightLeft(float Value);

	UFUNCTION()
	void Attack();

	UFUNCTION()
	void Attacked(float Value);

	UFUNCTION()
	void UpdateCharacterSprite();

    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    class USpringArmComponent* CameraBoom;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    class UCameraComponent* FollowCamera;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Animation)
    class UMainCharacterSpriteComponent* MainCharacterSpriteComponent;

	//for server 	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
public:
	float GetHealth(){
		return Health;
	}

	float GetMaxHealth(){
		return 100.0f;
	}

	UFUNCTION()
	void SetAttackAnimation();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State") 
	int32 WoodQuantity = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State") 
	int32 StoneQuantity = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State") 
	int32 MeatQuantity = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State") 
	int32 TrophyQuantity = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State") 
	int32 SwordLevel = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> DeathScreen;

	UFUNCTION()
	void EatMeat();

	UFUNCTION()
	void UpgradeSword();

private:

	UPROPERTY()
    class USphereComponent* SphereCollider;

	UPROPERTY()
	float TriggerRadius;

	bool WasSpawned = false;

	//Access to protected members for attacking system
	friend class AttackedActor;
	
	friend class AttackingActor;

	// Networked functions

	UFUNCTION(Server, Reliable)
	void ServerSetAttackAnimation();

	UFUNCTION()
	void EndAttackAnimation();

	UFUNCTION(Server, Reliable)
	void ServerEndAttackAnimation();

};